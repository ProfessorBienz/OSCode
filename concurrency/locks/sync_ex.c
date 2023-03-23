#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"
#include <sys/wait.h>
#include <sys/time.h>

semaphore_t sem;

void* mythread(void* arg)
{
    int* i = (int*) arg;

    if (*i == 0)
    {
        sem_wait(&sem);
        printf("Print this second!\n");
    }
    else if (*i == 1)
    {
        printf("Print this first!\n");
        sem_signal(&sem);
    }
    
    return NULL;
}

int main(int argc, char* argv[])
{
    int rc;
    int n = 2;

    sem_init(&sem, 0);

    int* thread_ids = (int*)malloc(n*sizeof(int));
    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    for (int i = 0; i < n; i++)
    {
        thread_ids[i] = i;
        rc = pthread_create(&(threads[i]), NULL, mythread, (void*)&(thread_ids[i]));
    }
    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

}
