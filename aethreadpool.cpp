#include "aethreadpool.h"

AE::AEThreadPool::AEThreadPool(int countThreads)
{
    threads.reserve(countThreads ? std::thread::hardware_concurrency() : countThreads);
    for(int i = 0; i< countThreads;i++)
    {
       // threads.emplace_back(AE::AETask([](){}));
    }

}

// void AE::AEThreadPool::execTask(AETask &task)
// {

// }




