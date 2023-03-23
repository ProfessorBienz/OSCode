// Portions from Patrick Bridges cs481 slides
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit()
{
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void* child(void* arg)
{
    volatile int s = 0;
    for (int i = 0; i < 10000000; i++)
        s++;
    printf("Child\n");
    thr_exit();
    return NULL;
}

void thr_join()
{
    pthread_mutex_lock(&m);
    while (done == 0)
        pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
}

int main(int argc, char* argv[])
{
    printf("Parent : begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    //pthread_join(p, NULL);    
    //thr_join();
    printf("Parent : end\n");
    return 0;
}
