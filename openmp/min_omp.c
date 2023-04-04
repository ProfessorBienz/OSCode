#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <sys/wait.h>
#include <sys/time.h>

#define MAX_THREADS 1000

double get_time()
{
    struct timeval timecheck;
    gettimeofday(&timecheck, NULL);
    return (double)timecheck.tv_sec + (double)timecheck.tv_usec*1e-6;
}


// This finds the minimum from a list without any checks
// This creates a race condition!  It may give the wrong answer!
void find_min_race(int* list, int list_size)
{
    int min_value = list[0];
    double start, end;

    start = get_time();
    #pragma omp parallel for shared(list, list_size)
    for (int i = 0; i < list_size; i++)
    {
        if (list[i] < min_value)
            min_value = list[i];
    }
    end = get_time();
    printf("Race Condition Version finds Min %d in %e seconds\n", min_value, end - start);
}

// Find minimum from a list with locks
// This is expensive, but correct
void find_min_lock(int* list, int list_size)
{
    int min_value = list[0];
    double start, end;

    omp_lock_t min_val_lock;
    omp_init_lock(&min_val_lock); 
    start = get_time();
    #pragma omp parallel for shared(list, list_size)
    for (int i = 0; i < list_size; i++)
    {
        omp_set_lock(&min_val_lock);
        if (list[i] < min_value)
            min_value = list[i];
        omp_unset_lock(&min_val_lock);
    }
    end = get_time();
    omp_destroy_lock(&min_val_lock);
    printf("Lock Version finds Min %d in %e seconds\n", min_value, end - start);
}

void find_min_critical(int* list, int list_size)
{
    int min_value = list[0];
    double start, end;

    start = get_time();
    #pragma omp parallel for 
    for (int i = 0; i < list_size; i++)
    {
        #pragma omp critical
        {
            if (list[i] < min_value)
                min_value = list[i];
        }
    }
    end = get_time();
    printf("Critical Version finds Min %d in %e seconds\n", min_value, end - start);
}

void find_min_local(int* list, int list_size)
{
    int n_threads;
    int min_value;
    double start, end;
    #pragma omp parallel
    {
        #pragma omp master
        n_threads = omp_get_num_threads();
    }

    int* min_vals = (int*)malloc(n_threads*sizeof(int));
    start = get_time();
    #pragma omp parallel shared(min_vals)
    {
        int id = omp_get_thread_num();
        min_vals[id] = list[0];
        #pragma omp for
        for (int i = 0; i < list_size; i++)
        {
           if (list[i] < min_vals[id])
              min_vals[id] = list[i];
        }
    } 
    min_value = min_vals[0];
    for (int i = 1; i < n_threads; i++)
    {
        if (min_vals[i] < min_value)
            min_value = min_vals[i];
    }
    end = get_time();
    printf("Local List Version finds Min %d in %e seconds\n", min_value, end - start);
    free(min_vals);
}

void find_min_master(int* list, int list_size)
{
    int min_value;
    double start, end;
    int min_vals[MAX_THREADS];
    start = get_time();
    #pragma omp parallel shared(min_vals)
    {
        int id = omp_get_thread_num();
        min_vals[id] = list[0];

        #pragma omp for
        for (int i = 0; i < list_size; i++)
        {
           if (list[i] < min_vals[id])
              min_vals[id] = list[i];
        }

        #pragma omp flush(min_vals)

        #pragma omp master
        {
            int n_threads = omp_get_num_threads();
            min_value = min_vals[0];
            for (int i = 1; i < n_threads; i++)
                if (min_vals[i] < min_value)
                    min_value = min_vals[i];
        }
    }
    end = get_time();
    printf("Master List Version finds Min %d in %e seconds\n", min_value, end - start);
}

void find_min_reduction(int* list, int list_size)
{
    int min_value = list[0];
    double start, end;

    start = get_time();
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < list_size; i++)
    {
        if (list[i] < min_value)
            min_value = list[i];
    }
    end = get_time();
    printf("Reduction Version finds Min %d in %e seconds\n", min_value, end - start);

}


int main(int argc, char* argv[])
{
    if (argc < 2) 
    {
        printf("Please state list_size\n");
        return 0;
    }


    int list_size = atoi(argv[1]);
    int* list = (int*)malloc(list_size*sizeof(int));
    srand(time(NULL));
    int min_value, min_pos;
    list[0] = rand();
    min_value = list[0];
    min_pos = 0;
    for (int i = 1; i < list_size; i++)
    {
        list[i] = rand();
        if (list[i] < min_value)
        {
            min_value = list[i];
            min_pos = i;
        }
    }
    printf("Actual Minimum Value %d at Position %d\n", min_value, min_pos);


    // Minimum Race Condition - Can give wrong answer!
    find_min_race(list, list_size);

    // Minimum Lock - Expensive!
    find_min_lock(list, list_size);

    // Minimum Critical - Slightly less expensive
    find_min_critical(list, list_size);

    // Minimum Local 
    find_min_local(list, list_size);

    // Minimum Master
    find_min_master(list, list_size); 

    // Minimum Reduction
    find_min_reduction(list, list_size);

    free(list);

    return 0;
}
