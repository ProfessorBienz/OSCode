#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#define _GNU_SOURCE
      
#include <pthread.h>
#include <sched.h>

typedef struct __semaphore_t 
{
    int S;
} semaphore_t;

void sem_init(semaphore_t* semaphore, int S)
{
    semaphore->S = S;
}

void sem_wait(semaphore_t* semaphore)
{
    semaphore->S--;
    while (semaphore->S < 0){}  
}

void sem_signal(semaphore_t* semaphore)
{
    semaphore->S++;
}

#endif
