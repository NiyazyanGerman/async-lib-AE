#ifndef AETASK_H
#define AETASK_H

#include <functional>
#include<thread>
#include"aetimer.h"

namespace AE {
enum class PriorityRunTask
{
    LOW_PRIORITY = 0,
    STANDART_PRIORITY = 1,
    HGH_PRIORITY = 2
};

class AETask
{
public:
    template<typename F>
    explicit AETask(AE::AETimer& duraction_after, F&& call_function,PriorityRunTask priority = PriorityRunTask::STANDART_PRIORITY)
    :
        current_rank_task(priority),
        timer(duraction_after)
    {
        current_function_object = std::forward<F>(call_function);
    }

    void operator()()
    {
        executeTask();
    }

    std::thread::id getIdTask() const &;

private:
    std::function<void()> current_function_object;
    PriorityRunTask current_rank_task = PriorityRunTask::STANDART_PRIORITY;
    AE::AETimer timer;
    int task_id;

    void executeTask()
    {
        if(current_function_object){
            // Pool(timer,current_function_object,priority)
        }

    }

    friend class CompareTaskByRank;


};

struct CompareTaskByRank {
    bool operator()(const AETask& task_first, const AETask& task_second) const {
        return task_first.current_rank_task > task_second.current_rank_task;
    }
};


}
#endif // AETASK_H
