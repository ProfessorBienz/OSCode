#include <stdio.h>

void update_ptr(int* i_ptr)
{
    int val = 1;
    *i_ptr = val;
    printf("Method 0 : setting the value at address %p to %d\n", i_ptr, *i_ptr);
}

void update_ptr_incorrect(int* i_ptr)
{
    int val = 2;
    printf("Method 1 : replacing address %p with address %p\n", i_ptr, &val);
    i_ptr = &val;
}

void update_i_incorrect(int i)
{
    int val = 3;
    i = val;
    printf("Method 2 : address of i is %p\n", &i);
}

int main(int argc, char* argv[])
{
    int i = 0;
    
    update_ptr(&i);
    printf("The method update_ptr works, because we are updating the value at the address i_ptr.  After method, i = %d\n\n", i);

    update_ptr_incorrect(&i);
    printf("The method update_ptr_incorrect does not work, because we are trying to replace the address of i_ptr with the address of val.  On return of the method, we still hold the original address of i.  After this method, i = %d (not 2)\n\n", i);

    update_i_incorrect(i);
    printf("The address of i in main is %p\n\n", &i);
}
