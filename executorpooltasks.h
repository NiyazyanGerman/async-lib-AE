#ifndef EXECUTORPOOLTASKS_H
#define EXECUTORPOOLTASKS_H
#include "aetask.h"
#include<thread>
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

    AE::AETask setTask(PriorityRunTask priority = 1);
    auto getReturnValueTask();
private:
    int* workerThreads=nullptr;
};

#endif // EXECUTORPOOLTASKS_H
