#include "scheduler.h"

#include <utility>

Scheduler::Scheduler(int workerCount)
    : workerCount_(workerCount){}

void Scheduler::start()
{
    if (started_) {
        return;
    }

    started_ = true;

    for (int i = 0; i < workerCount_; ++i) {
        workers.emplace_back(&Scheduler::workerLoop, this);
    }
}

void Scheduler::submit(Task task)
{
    queue.push(std::move(task));
}

void Scheduler::workerLoop()
{
    Task task;

    while (queue.pop(task)) {
        task();
    }
}

void Scheduler::shutdown()
{
    queue.shutdown();

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    workers.clear();
    started_ = false;
}