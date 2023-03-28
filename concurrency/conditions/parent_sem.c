// Portions from Patrick Bridges cs481 slides
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


void* child(void* arg)
{
    sem_t* s = sem_open("parent_child_sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    volatile int x = 0;
    for (int i = 0; i < 10000000; i++)
        x++;
    printf("Child\n");
    sem_post(s);
    sem_close(s);
    return NULL;
}

int main(int argc, char* argv[])
{
    sem_t* s = sem_open("parent_child_sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
    printf("Parent : begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    sem_wait(s);
    printf("Parent : end\n");
    sem_close(s);
    sem_unlink("parent_child_sem");
    return 0;
}
