#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("hello world (pid: %d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }
    else if (rc == 0)
    {
        int rc2 = fork();
        if (rc2 == 0)
            printf("Grandchild here (pid %d)\n", (int) getpid());
        else
            printf("Hello, I am child (pid: %d)\n", (int) getpid());
    }
    else
    {
        wait(NULL);
        printf("Hello, I am the parent of %d (pid: %d)\n", rc, (int) getpid());
    }

    return 0;
}
