/* TODO: Add necessary header files here */
#include <stdio.h>
#include <unistd.h>
#include "mm_public.h"

int main() {
    /*
     * TODO: Write the code to time your memory manager (mm_t)
     * according to section 2.4 of the writeup
     */
    mm_t MM;
    mm_init(&MM, 10000, 64);
    struct timeval time_start, time_end;
    int i, j;
    void* num[10000];

    j = gettimeofday (&time_start, (void *)NULL);

    for (i = 0; i < 10000; i++)
    {
        num[i] = mm_get(&MM);
    }
    for (i = 0; i < 10000; i++)
    {
        mm_put(&MM, num[i]);
    }
    j = gettimeofday (&time_end, (void *)NULL);

    printf ("Time taken using memory manager = %f msec\n",
            comp_time (time_start, time_end)/1000.0);
}

