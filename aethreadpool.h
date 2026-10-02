#ifndef AETHREADPOOL_H
#define AETHREADPOOL_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "aetask.h"
#include "aetimer.h"

namespace AE {

class ExecutorPoolTasks;
using taskFunc = AE::AETask;

class AEThreadPool
{
public:
    explicit AEThreadPool(int countThreads = std::thread::hardware_concurrency());
    ~AEThreadPool();

    static inline AEThreadPool* instance() {
        static AEThreadPool pool;
        return &pool;
    }

    void execTask(AETask &task);
    void worker_loop();

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::priority_queue<AE::AETask, std::vector<AE::AETask>, AE::CompareTaskByRank> pr_queue_tasks;

    std::vector<std::thread> threads;
    int countWorkerThread_;

    std::thread getThread();
    void initProcces();

    friend class ExecutorPoolTasks;
};

} // namespace AE

#endif // AETHREADPOOL_H
