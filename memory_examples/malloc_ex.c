#include "stdlib.h"
#include "stdio.h"

// Run this file with 'strace'
// e.g. 'strace ./malloc_ex <number>'
// to see system calls associated with 
// allocating data in the heap
int main(int argc, char* argv[])
{
    if (argc < 1)
    {
	    printf("Need Command Line Arg\n");
	    return 0;
    }
    int n = atoi(argv[1]);
    int* a = (int*)malloc(n*sizeof(int));

    free(a);
}
