#pragma once // This tells the compiler to only include the headder file once.

#include <queue>
#include <mutex> // Protects the queue when multiple threads access it
#include <condition_variable> // lets the workers sleep when there are not tasks to do 
#include <functional> // normally you call a function directly, this allows us to store a callable for later usage. 

using Task = std::function<void()>; // task is the name of my function that takes nothing and returns nothing, because in all honesty
// the queue should not care about what kinda work its going to be doing just that there is a task to be done

class TaskQueue{
    private:
        std::queue<Task> tasks_;    
        std::mutex mutex_;
        std::condition_variable cv_;
        bool stopping_ = false;
    public:
        void push(Task task);
        bool pop(Task & task);
        void shutdown();
};
