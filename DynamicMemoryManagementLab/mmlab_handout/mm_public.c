#include "mm_public.h"

/*
 * Returns time difference between "timee" and "times" in micro-seconds (usec)
 */
double comp_time (struct timeval times, struct timeval timee) {

    double elap = 0.0;

    if (timee.tv_sec > times.tv_sec) {
        elap += (((double)(timee.tv_sec - times.tv_sec -1))*1000000.0);
        elap += timee.tv_usec + (1000000-times.tv_usec);
    }
    else {
        elap = timee.tv_usec - times.tv_usec;
    }

    return ((unsigned long)(elap));
}

/*
 * TODO
 * Allocate the big memory
 * Return 0 on success
 * Return -1 on failure
 */
int mm_init (mm_t* MM, int howmany, int size)
{
    //check for number error
    if (howmany <= 0)
    {
        printf("Invalid number of chunks.\n");
        return -1;
    }
    if (size <= 0)
    {
        printf("Invalid number of size.\n");
        return -1;
    }

    void* my_ptr;
    int i;
    //malloc for array of integers
    MM->mm_heap = (int*)malloc(sizeof(int)*howmany);
    if (MM->mm_heap == NULL)
    {
        perror("Mallocing of the array failed.");
        return -1;
    }

    for(i = 0; i < howmany; i++)
    {
        MM->mm_heap[i] = i;
    }

    my_ptr = malloc(howmany*size);
    if (my_ptr == NULL)
    {
        perror("Malloc failed big time");
        return -1;
    }

    MM->chunk_pointers = my_ptr;
    MM->count_chunk = howmany;
    MM->chunk_size = size;
    MM->free_chunk = howmany - 1;
    return 0;
}

/*
 * TODO
 * Get a chunk of memory
 * On success: Return pointer to void
 * On failure: Return NULL
 */
void* mm_get (mm_t *MM)
{
    if (MM->free_chunk < 0)
    {
        printf("No available chunk.\n");
        return NULL;
    }
    void* address = NULL;
    int index;
    index = MM->free_chunk;
    address = MM->chunk_pointers + (MM->mm_heap[index])*(MM->chunk_size);

    MM->free_chunk--;
    return address;
}

/*
 * TODO
 * Give back chunk of your memory manager
 * DON'T free it the_arrayough!
 */
void mm_put (mm_t *MM, void *chunk)
{
    int index;
    index = chunk - MM->chunk_pointers;
    if (index % MM->chunk_size != 0)
    {
        printf("Invalid pointer to chunk.\n");
        return;
    }
    index = index/(MM->chunk_size);
    MM->free_chunk++;
    MM->mm_heap[MM->free_chunk] = index;
}

/*
 * TODO
 * Release the big memory back to the system
 */
void mm_release (mm_t *MM)
{
    free(MM->mm_heap);
    free(MM->chunk_pointers);
}

/*
 * Example on how to use "comp_time" to time your code
 * Print the time difference in milli-seconds (msec)
 */
void timer_example ()
{
    struct timeval time_start, time_end;
    int j;

    /* start timer */
    j = gettimeofday (&time_start, (void *)NULL);

    /* Code you wish to time goes here */

    j = gettimeofday (&time_end, (void *)NULL);

    fprintf (stderr, "Time taken =  %f msec\n",
             comp_time (time_start, time_end)/1000.0);
}
