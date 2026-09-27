#ifndef AETASK_H
#define AETASK_H

namespace AE {

class AETask
{
public:
    template<class F>
    AETask(F&& function);
private:

    int task_id;

};

}
#endif // AETASK_H
