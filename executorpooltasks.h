#ifndef EXECUTORPOOLTASKS_H
#define EXECUTORPOOLTASKS_H
#include "aetask.h"
#include<thread>
#include"aethreadpool.h"
#include"aetimer.h"
class ExecutorPoolTasks
{
    enum class PriorityRunTask
    {
        LOW_PRIORITY = 0,
        STANDART_PRIORITY = 1,
        HGH_PRIORITY = 2
    };

public:
    ExecutorPoolTasks();

    void initPool(int threadsWorker = std::thread::hardware_concurrency())
    {
        workerThreads = new int(threadsWorker);
    }

    ~ExecutorPoolTasks()
    {
        delete workerThreads;
    }

    void run(AE::AETask& taskFunc);


    auto getReturnValueTask();

private:
    int* workerThreads=nullptr;
    AE::AEThreadPool* pool;

    friend class AE::AEThreadPool;
};

#endif // EXECUTORPOOLTASKS_H
