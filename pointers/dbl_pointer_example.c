#include <stdio.h>
#include <stdlib.h>

void update_ptr(int** i_ptr)
{
    int* val = (int*)malloc(sizeof(int));
    val[0] = 1;
    *i_ptr = val;
    printf("Method 0 : setting the value at address %p to point to %p (which holds value %d)\n", i_ptr, *i_ptr, **i_ptr);
}

void update_ptr_incorrect(int** i_ptr)
{
    int* val = (int*)malloc(sizeof(int));
    val[0] = 2;
    printf("Method 1 : replacing address of i_pointer %p with pointer to address of val %p\n", i_ptr, &val);
    i_ptr = &val;
    free(val); // need to free, because this is not returned in this case
}

void update_i_incorrect(int* i)
{
    int* val = (int*)malloc(sizeof(int));
    val[0] = 3;
    printf("Method 2 : replacing address of i %p with address of val %p\n", i, val);
    i = val;
    free(val); // need to free, because this is not returned in this case
}

int main(int argc, char* argv[])
{
    int* i;
    printf("\nAfter declaring i, the address pointing to i (e.g. i_ptr) is %p\n", &i);
    
    // Correct Way! 
    update_ptr(&i);
    printf("The method update_ptr works, because we are setting the value at the address i_ptr to hold the address of 'val'.  After method, the address of i is %p, which holds the value %d\n\n", i, *i);

    // Incorrect Way 1!
    update_ptr_incorrect(&i);
    printf("The method update_ptr_incorrect does not work, because we are trying to replace the address of i_ptr with the address of val.  After this method, the address of i remains %p, which holds the value %d\n\n", i, *i);

    // Incorrect Way 2!
    update_i_incorrect(i);
    printf("The method update_i_incorrect does not work, because we are trying to replace the address of i with the address of val.  After this method, the address of i is %p, which holds the value %d\n\n", i, *i);

    free(i);
}
