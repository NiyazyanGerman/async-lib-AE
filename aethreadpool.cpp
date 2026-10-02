#include "aethreadpool.h"
#include <iostream>

AE::AEThreadPool::AEThreadPool(int countThreads)
{
    int actualThreads = (countThreads <= 0) ? std::thread::hardware_concurrency() : countThreads;

    threads.reserve(actualThreads);

    for(int i = 0; i < actualThreads; i++)
    {
        threads.emplace_back(&AE::AEThreadPool::worker_loop, this);
    }
}

void AE::AEThreadPool::worker_loop()
{
    while(true)
    {
        AE::AETask task_to_execute;
        {
            std::unique_lock<std::mutex> ulm(mtx);

            // ИСПРАВЛЕНО: Поток проснется, если есть задача ИЛИ если пул закрывается
            cv.wait(ulm, [this](){
                return !pr_queue_tasks.empty() || stop_pool;
            });

            // Если задач больше нет и приказано остановиться — выходим из потока
            if (stop_pool && pr_queue_tasks.empty()) {
                return;
            }

            // Поток берёт задачу здесь!
            task_to_execute = std::move(const_cast<AE::AETask&>(pr_queue_tasks.top()));
            pr_queue_tasks.pop();
        }

        // Вызов задачи (запуск твоей лямбды с Hello World)
        task_to_execute();
    }
}

void AE::AEThreadPool::execTask(AETask &task)
{
    {
        std::unique_lock<std::mutex> ulm(mtx);
        pr_queue_tasks.push(std::move(task));
    }
    cv.notify_one(); // Будим поток
}

AE::AEThreadPool::~AEThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop_pool = true; // ИСПРАВЛЕНО: Выставляем флаг остановки пула
    }

    // Будим все потоки. Теперь они увидят флаг stop_pool и выйдут из cv.wait
    cv.notify_all();

    // Главный поток ждет, пока все рабочие красиво завершатся
    for (std::thread &th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
}
