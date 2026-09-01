#include "task_queue.h"

// 1. Implement this first
/*
lock guard can hold diffrent kinds of locks, the type this is holding is a mutex. 
std::lock_guard<std::mutex> is its type. 
its saying 
- lock guard -> please use the locking behavior provided by mutex
- we could use just mutex but then we would have to manually unlock each part ie: the cleanup is tied to the objects life time. 
- we dont even want to use mutex by its self because we can use other things like unique_lock which provides that functionality in a cleaner manner. 

lock = the name of the lock guard object we are creating. 
mutex_ = Construct lock and give it this spesific mutex to manage 
-> this was reated in the task_queue.h file, inside of the TaskQueue as a private attribute it is a mutex called mutex_
- a mutex is a synchronization object that ensures only one thread at a time can access a protected section of code / data. 
-------------------------------------------------------------------------------------------------------------
tasks_.push(std::move(task));

- Add something to the back of our task queue.
If we just did tasks_.push(task); then that would copy the task into the queue, instead what we do is we say that we dont need our task
anymore so we say lets use move semantics, and allow the queue to move its resources into the new queue element, but this is just a suggestion that you can
change ownership not a definitive, which would be cheaper than a copy. 
-------------------------------------------------------------------------------
 cv_.notify_one(); is an std::condition_variable.
 - think of it as a sleep and wake up mechanism for threads. 
 - creates and object that threads can use to (wait, or wake up)
 - cv_ belongs to the queue, not to individual tasks.
 It basicly means Wake up one worker that is currently sleeping on this condition variable.
 --------------------------------------------------------------------------------------------

*/
void TaskQueue::push(Task task) {
{  
    std::lock_guard<std::mutex> lock(mutex_);

    tasks_.push(std::move(task));
}
    cv_.notify_one();
}

// 2. Then this

/*
std::unique_lock<std::mutex> lock(mutex_);

- Create an unique_lock called lock that takes control of mutex_
We do this because a worker might find out that the queue is empty and as such they need to sleep until a task arrives. it needs to do a lot
1. Lock mutex, 2. Check queue, 3. Queue empty → UNLOCK mutex, 4. Sleep, 5. Get notified, 6. LOCK mutex again, 7. Check queue






*/


bool TaskQueue::pop(Task& task) {
    std::unique_lock<std::mutex> lock(mutex_);

    cv_.wait(lock, [this] { return !tasks_.empty() || stopping_;});

    if(stopping_ && tasks_.empty()){return false;}

    task = std::move(tasks_.front());
    tasks_.pop();
    return true;
}



// 3. Finally this
void TaskQueue::shutdown() {

}