#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *mythread(void* arg)
{
    uint64_t tid;
    pthread_threadid_np(NULL, &tid);
    printf("Hello World from Thread : %llu\n", tid);
    return NULL;
}

int main(int argc, char* argv[])
{
    int n = 2;
    int* ids = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
        ids[i] = i;
    pthread_t* p = (pthread_t*)malloc(n*sizeof(pthread_t));
    int rc;
    for (int i = 0; i < n; i++)
        rc = pthread_create(&(p[i]), NULL, mythread, &(ids[i]));
    for (int i = 0; i < n; i++)
        pthread_join(p[i], NULL);
}
