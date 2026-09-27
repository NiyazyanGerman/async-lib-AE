#ifndef AETHREADPOOL_H
#define AETHREADPOOL_H
#include<functional>
#include<queue>
#include<thread>

namespace AE {
using taskFunc = std::function<void()>;

class AEThreadPool
{
public:
   explicit AEThreadPool(int countThreads = 1);

    void execTask(taskFunc task);

private:
   int countWorkerThread_;

    std::thread getThread();


};

}


#endif // AETHREADPOOL_H
