# CS252_Project
## About The Project
The project has implementation of two different projects:
1. CPU Scheduling Implementation
2. Designing a threadpool
Each have been assigned a specific folder with all the required files within their respective folder 

## Project 1: CPU Scheduling Algorithm

This project involves implementing several different process scheduling algorithms. 
The scheduler will be assigned a set of tasks that is inputted by the user and will schedule the tasks based on all the scheduling algorithm. 
Each task is assigned a priority and CPU burst. The following scheduling algorithms will be implemented:
• First-come, first-served (FCFS), which schedules tasks in the order in which they request the CPU.
• Shortest-job-first (SJF), which schedules tasks in order of the length of the tasks’ next CPU burst.
• Priority scheduling, which schedules tasks based on priority. 
• Round-robin (RR) scheduling, where each task is run for a time quantum (or for the remainder of its CPU burst).
• Priority with round-robin, which schedules tasks in order of priority and uses round-robin scheduling for tasks with equal priority.
Priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority. For round-robin scheduling, 
the length of a time quantum is 10 milliseconds.

Each of the algorithm has a specified function associated with it which is called onto the main function.
The tasks are all taken in order of their naming convention, that is T1, T2 and so on and the output is displayed in tables for each of the scheduling algorithm (although skewed). 
Some difficulties faced were more entailing towards the implementation of round robin and priority round robin.

### How to execute?

CPU_Scheduling.c has to be run. It uses stdlib and stdio libraries.

## Project 2: Designing a threadpool
The user file is client.c which submits task to the thread pool.
The thread is assigned to a particular task in the file threadpool.c which makes use of user defined library threadpool.h.
The makefile is used to build the project and generate the final binary "output".

This project folder was taken from the github repo "https://github.com/xalstnx/3_1-operating-system-project2"


### Execution
1. Clone repository
2. Go to the threadpool directory
3. To compile using appropirate flags and generate binary named output, use make command
4. The output can be seen by listing the "output" file

## Credits
### CPU Scheduling
Used GFG, JavaTutorials as guides to understand and implement the various scheduling algorithm.
### Designing a threadpool
This project folder was taken from the github repo "https://github.com/xalstnx/3_1-operating-system-project2". All credits to xlastnx.
