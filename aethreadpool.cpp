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

            cv.wait(ulm, [this](){
                return !pr_queue_tasks.empty();
            });



            task_to_execute = std::move(const_cast<AE::AETask&>(pr_queue_tasks.top()));
            pr_queue_tasks.pop();
        }

        task_to_execute();
    }
}

void AE::AEThreadPool::execTask(AETask &task)
{
    {
        std::unique_lock<std::mutex> ulm(mtx);
        pr_queue_tasks.push(std::move(task));
    }
    cv.notify_one();
}

AE::AEThreadPool::~AEThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mtx);
    }

    cv.notify_all();

    for (std::thread &th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
}
