#include "executorpooltasks.h"

ExecutorPoolTasks::ExecutorPoolTasks() {

    pool = AE::AEThreadPool::instance();


}

void ExecutorPoolTasks::run(AE::AETask &taskFunc)
{
    AE::AEThreadPool::instance()->execTask(taskFunc);
}
