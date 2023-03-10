// Portions from Patrick Bridges cs481 slides
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

void* mythread(void* arg)
{
    int* m = (int*) arg;

    int local_m = 0;
    for (int i = 0; i < 1000; i++)
    {
        local_m = local_m + 1;
    }
    pthread_mutex_lock(&lock);
    *m = *m + local_m;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char* argv[])
{
    int rc;
    int m = 0;
    int n = 100;

    rc = pthread_mutex_init(&lock, NULL);

    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    for (int i = 0; i < n; i++)
        rc = pthread_create(&(threads[i]), NULL, mythread, (void*)&m);

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    printf("M : %d\n", m);
}
