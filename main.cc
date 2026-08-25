/*
Project 2
Concurrent Task Scheduler
Covers:
threads
mutexes
atomics
memory ordering
false sharing
affinity
NUMA basics
*/




/*
! We are going to be doing this one task at a time so what that means is lets develop the first task which will be a (CPU MATH TASK) we are then going to go through
! all phases so from task -> task queue -> scheudling workers -> execution. 

1. TASKS : 3-5 Tasks
   "Here is work that needs doing"
   1. CPU Math Task
   2. Array Sort Task
   3. Memory Scan Task
   4. Shared Counter Task
   5. Producer/Consumer Task
        │
        ▼
2. TASK QUEUES
   "Here is the work waiting to run"
        │
        ▼
3. SCHEDULING / WORKERS
   "Who should execute the next task?"
        │
        ▼
4. EXECUTION + RESULTS
   Run task → finish → return/store result



*/