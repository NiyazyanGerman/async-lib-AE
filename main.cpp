#include <iostream>
#include"aethreadpool.h"
#include<algorithm>
#include"executorpooltasks.h"
#include<iostream>
int main(int argc, char *argv[])
{
    std::cout<<std::this_thread::get_id()<<"\n";
    ExecutorPoolTasks ept;
    ept.initPool();

    AE::AETimer my_timer;

    AE::AETask my_task2(
        my_timer,
        [](){
            std::cout << "[Thread ID: " << std::this_thread::get_id() << "]  World" << std::endl;
        },
        AE::PriorityRunTask::LOW_PRIORITY
        );

    AE::AETask my_task(
        my_timer,
        [](){
             std::cout << "[Thread ID: " << std::this_thread::get_id() << "] Hello World" << std::endl;
        },
        AE::PriorityRunTask::HGH_PRIORITY
        );


    ept.run(my_task2);
    ept.run(my_task);

}
