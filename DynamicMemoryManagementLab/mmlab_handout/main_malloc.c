/* TODO: Add necessary header files here */
#include <stdio.h>
#include <unistd.h>
#include "mm_public.h"

int main() {
    /*
     * TODO: Write the code to time malloc and free
     * according to section 2.4 of the writeup
     */
    struct timeval time_start, time_end;
    int i, j;
    void* ptr[10000];

    j = gettimeofday (&time_start, (void *)NULL);

    for (i = 0; i < 10000; i++)
    {
        ptr[i] = malloc(64);
    }
    for (i = 0; i < 10000; i++)
    {
        free(ptr[i]);
    }
    j = gettimeofday (&time_end, (void *)NULL);

    printf("Time taken = %f msec\n",
            comp_time (time_start, time_end)/1000.0);
}
