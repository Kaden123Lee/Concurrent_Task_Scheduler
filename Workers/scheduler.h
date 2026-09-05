#pragma once

#include <thread>
#include <vector>

#include "../Task_Scheduler/task_queue.h"

class Scheduler {
private:
    // The shared queue containing tasks waiting to run
    TaskQueue queue;

    // The actual worker threads
    std::vector<std::thread> workers;

    // How many worker threads should exist
    int workerCount_;

    // Prevents start() from creating workers twice
    bool started_ = false;

    // Code that every worker thread runs
    void workerLoop();

public:
    // Create a scheduler configured for N workers
    explicit Scheduler(int workerCount);

    // Create/start the worker threads
    void start();

    // Give the scheduler a new task
    void submit(Task task);

    // Stop the queue and wait for all workers to finish
    void shutdown();
};