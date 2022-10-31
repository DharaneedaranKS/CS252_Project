# CS252_Project
## About The Project
This repository has implementation of two different projects:
1. CPU Scheduling Implementation
2. Designing a threadpool
Each have been assigned a specific folder with all the required files within their respective folder 

## Project 1: CPU Scheduling Algorithm

This project involves implementing several different process scheduling algorithms. 
The scheduler will be assigned a set of tasks that is inputted by the user and will schedule the tasks based on all the scheduling algorithm. 
Each task is assigned a priority and CPU burst. The following scheduling algorithms will be implemented:<br />
• First-come, first-served (FCFS), which schedules tasks in the order in which they request the CPU.<br />
• Shortest-job-first (SJF), which schedules tasks in order of the length of the tasks’ next CPU burst.<br />
• Priority scheduling, which schedules tasks based on priority. <br />
• Round-robin (RR) scheduling, where each task is run for a time quantum (or for the remainder of its CPU burst).<br />
• Priority with round-robin, which schedules tasks in order of priority and uses round-robin scheduling for tasks with equal priority.<br />
Priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority. For round-robin scheduling, 
the length of a time quantum is 10 milliseconds.

Each of the algorithm has a specified function associated with it which is called onto the main function.
The tasks are all taken in order of their naming convention, that is T1, T2 and so on and the output is displayed in tables for each of the scheduling algorithm (although skewed). 
Some difficulties faced were more entailing towards the implementation of round robin and priority round robin.

### How to execute?

CPU_Scheduling.c has to be run. It uses stdlib and stdio libraries.

## Project 2: Designing a threadpool
The user file is client.c which has a set of predefined tasks such as add, print series of numbers, etc which is assigned in a sequence to a thread pool by calling the pool_submit function which is implemented in threadpool.c.<br /> In threadpool.c, we load the pthread, semaphores library as well as the programmer defined library threadpool.h. In the pool_submit function, the given task is added to the task queue which serves as a buffer. If the queue is full, it returns 1 and the task has to wait to be able to get added to the queue. The task is then assigned a thread from the thread pool by calling pthread_create which makes use of the worker function where a semaphore is made use of to remove a task from the queue and then execute it.<br />
The function pool_init is used to initialise threads to the thread pool and the function pool_shutdown closes down the thread pool <br />
The makefile is used to build the project and generate the final binary "example".

This project folder was taken from the github repo "https://github.com/xalstnx/3_1-operating-system-project2"


### Execution
1. Clone repository ( git clone https://github.com/DharaneedaranKS/CS252_Project.git' )
2. Go to the threadpool directory ( cd /<Download folder>/CS252_Project/Threadpools/ )
3. To compile using appropirate flags and generate binary named output, use make command 
4. The output can be seen by listing the "example" file ( >> ./example )

## Credits
### CPU Scheduling
Used GFG, JavaTutorials as guides to understand and implement the various scheduling algorithm.
### Designing a threadpool
This project folder was taken from the github repo "https://github.com/xalstnx/3_1-operating-system-project2". All credits to xlastnx.
