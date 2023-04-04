#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

// Serial Function for approximating pi
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Please add number of samples\n");
        return 0;
    }

    long n_samples = atol(argv[1]);
    long n_in_circle = 0;
    double rand_x, rand_y;

    // Seed random number generator
    srand(time(NULL));

    // Calculate random x and y values, between 0 and 1
    #pragma omp parallel for default(shared) private(rand_x, rand_y) reduction(+:n_in_circle)
    for (long i = 0; i < n_samples; i++)
    {
       rand_x = (double)(rand()) / RAND_MAX;  // X is between 0 and 1
       rand_y = (double)(rand()) / RAND_MAX;  // Y is between 0 and 1

       // If inside circle, add to n_in_circle
       if ((rand_x*rand_x) + (rand_y*rand_y) <= 1)
           n_in_circle++;
    }

    // Pi is approximately 4 * number in circle / total number in square
    double pi = 4.0*n_in_circle / n_samples;


    printf("NSamples %ld, Pi Approx %e\n", n_samples, pi);

    return 0;
}
