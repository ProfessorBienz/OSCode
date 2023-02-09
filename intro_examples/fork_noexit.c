#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>


int create_child()
{
    int rc = fork();
    
    if (rc == 0)
        printf("Child Here\n");
    else printf("Parent of %d\n", rc);

    return rc;
}

int main(int argc, char* argv[])
{
    int rc = create_child();

    printf("Process at end of main method rc = %d\n", rc);

    if (rc == 0)
        _exit(0);

    return 0;
}
