#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

// this represents work that has to be 
// completed by a thread in the pool

sem_t semqueue;

//Struct to keep track of how many tasks are in the queue and need a thread from the thread pool
typedef struct 
{
    void (*function)(void *p);
    void *data;
}task;

task queue[QUEUE_SIZE];
int queuenum = 0;
int deqcurpos = 0;
int enqcurpos = 0;

// the work queue
task worktodo; //Used to store the work that has to be done, used in dequeue function

task enqwork; //used in pool submit while submitting work to pool

// threads being declared 
pthread_t bee1;
pthread_t bee2;
pthread_t bee3;

int choosethread = 0; //variable to keep track of how many threads are available

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enqueue(task t) 
{
    sem_wait(&semqueue);
    if(queuenum > 10){
	sem_post(&semqueue); //Release semaphore
	return 1;
    }
    queue[enqcurpos] = t; //add task to work queue
    queuenum ++;
    enqcurpos = (enqcurpos + 1)%10;
    sem_post(&semqueue);
    return 0;
}

// remove a task from the queue
task dequeue() 
{
    worktodo = queue[deqcurpos]; //get task to be done
    deqcurpos = (deqcurpos + 1)%10;
    return worktodo;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    task newwork;
    sem_wait(&semqueue);
    if(queuenum != 0){
	queuenum--; //reduce no of tasks in the queue
	newwork = dequeue(); //obtain the task to be performed
	(*newwork.function)(newwork.data);
	//queuenum--;
    }
    sem_post(&semqueue);
    pthread_exit(0); //terminates calling thread
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    enqwork.function = somefunction;
    enqwork.data = p;
    int eq = enqueue(enqwork); //returns 0 if entry to queue is successful otherwise returns 1

    if(choosethread  == 0){
    	pthread_create(&bee1,NULL,worker,NULL);
    }else if(choosethread == 1){
	pthread_create(&bee2,NULL,worker,NULL);
    }else if(choosethread == 2){
	pthread_create(&bee3,NULL,worker,NULL);
    }
    choosethread = (choosethread + 1)%3;

    return eq;
}

// initialize the thread pool
void pool_init(void)
{
    sem_init(&semqueue,0,1); //Initialising semaphore which can't be shared between processes, with count as 1
}

// shutdown the thread pool
void pool_shutdown(void)
{
    pthread_join(bee1,NULL);
    pthread_join(bee2,NULL);
    pthread_join(bee3,NULL);
}
