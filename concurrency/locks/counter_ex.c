// Portions from Patrick Bridges cs481 slides
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>

double get_time()
{
    struct timeval timecheck;
    gettimeofday(&timecheck, NULL);
    return (double)timecheck.tv_sec + (double)timecheck.tv_usec*1e-6;
}


typedef struct __counter_t 
{
    int value;
    pthread_lock_t lock;
} counter_t;

void init(counter_t* c)
{
    c->value = 0;
    pthread_mutex_init(&(c->lock), NULL);
}

void increment(counter_t* c)
{
    pthread_mutex_lock(&(c->lock), NULL);
    c->value++;
    pthread_mutex_unlock(&(c->lock), NULL);
}

void decrement(counter_t* c)
{
    pthread_mutex_lock(&(c->lock), NULL);
    c->value--;
    pthread_mutex_unlock(&(c->lock), NULL);
}

int get(counter_t* c)
{
    pthread_mutex_lock(&(c->lock), NULL);
    int rc = c->value;
    pthread_mutex_unlock(&(c->lock), NULL);
    return rc;

}

void *mythread(void* arg)
{
    counter_t* c = (counter_t*)arg;

    for (int i = 0; i < 500000; i++)
        increment(c);
    for (int i = 0; i < 500000; i++)
        decrement(c);
}

int main(int argc, char* argv[])
{
    int rc;
    int n = 100;
    counter_t c;
    init(&c);

    double t0 = get_time();

    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    for (int i = 0; i < n; i++)
        rc = pthread_create(&(threads[i]), NULL, mythread, (void*)&c);

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    double tfinal = get_time() - t0;

    printf("Counter : %d, Time : %e\n", c.value, tfinal);
}
