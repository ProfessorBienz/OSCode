#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// compile with gcc -o hello_world_omp hello_world_omp.c -fopenmp

// Main Method
int main(int argc, char* argv[])
{
    //int n_threads = 7;
    //int thread_id;

    // OpenMP statement, each thread has own n_threads and thread_id variables (so private)
    #pragma omp parallel
   // private(thread_id) shared(n_threads)
    {
        // Get number of threads and id of current thread
        int n_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        // Print hello world
//        for (int i = 0; i < n_threads; i++)
//        {
//            if (thread_id == i)
                printf("Hello World from Thread %d\n", thread_id);
//        }
#pragma omp barrier

        // Have thread 0 print the number of threads
        //if (thread_id == 0) printf("Number of threads is %d\n", n_threads);
    }

    printf("Nthreads %d\n", n_threads);

    return 0;
}
