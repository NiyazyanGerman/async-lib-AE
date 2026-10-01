#ifndef AETHREADPOOL_H
#define AETHREADPOOL_H
#include "aetask.h"
#include <condition_variable>
#include<queue>
#include<thread>
#include"aetimer.h"


namespace AE {

class ExecutorPoolTasks;
using taskFunc = AE::AETask;

class AEThreadPool
{
public:
   explicit AEThreadPool(int countThreads = std::thread::hardware_concurrency());

    void execTask(AE::AETask& task,AE::AETimer& timer,PriorityRunTask priority);

private:
    int countWorkerThread_;

    std::thread getThread();

    std::condition_variable cv;
    std::priority_queue<AE::AETask, std::vector<AE::AETask>, AE::CompareTaskByRank> pr_queue_tasks;
    std::mutex mtx;
    std::vector<std::thread> threads;
    void initProcces();

friend class ExecutorPoolTasks;

};

}


#endif // AETHREADPOOL_H
