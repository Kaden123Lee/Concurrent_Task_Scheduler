#include <iostream>
#include "Workers/scheduler.h"

int main() {
    Scheduler scheduler(4);

    scheduler.start();

    std::mutex coutMutex;

   for (int i = 0; i < 10; ++i) {
      scheduler.submit([i, &coutMutex] {
         std::lock_guard<std::mutex> lock(coutMutex);
         std::cout << "Running task " << i << '\n';
      });
   }

    scheduler.shutdown();

    return 0;
}


/*
Which worker executes each task?
How evenly are tasks distributed between workers?
How much faster are 2, 4, 8, 16 workers than 1?
At what worker count does performance stop improving? Why?
How long does a task wait in the queue before execution?
How long does each task actually execute?
How much scheduler overhead exists for very small tasks?
Does task size change the optimal worker count?
What happens if there are more workers than CPU cores?
Where is contention occurring in the current shared-queue design
*/
