/* Rain Xuanyu Zhang
 * zhan2223
 * ID: 4642453
 *
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The replacement policy is LRU.
 *
 * The function printSummary() is given to print output.
 * Please use this function to print the number of hits, misses and evictions.
 * This is crucial for the driver to evaluate your work.
 */
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

//#define DEBUG_ON
#define ADDRESS_LENGTH 64

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line
   LRU is a counter used to implement LRU replacement policy  */
typedef struct cache_line {
    char valid;
    mem_addr_t tag;
    unsigned long long int lru;
} cache_line_t;

typedef cache_line_t* cache_set_t;
typedef cache_set_t* cache_t;

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;

/* The cache we are simulating */
cache_t cache;
mem_addr_t set_index_mask;

int getSetBits(mem_addr_t* addr)
{
    int temp;
    temp = (1 << s) - 1;
    return (int)(temp & ((long)addr >> b));
}

long getTagBits(mem_addr_t* addr)
{
    return (long)((long)addr >> (s + b));
}

void initCache()
{
    int tS = (1 << s);
    if (tS <= 0)
    {
        fprintf(stderr, "S is nonpositive\n");
        exit(0);
    }

    cache = (cache_t)malloc(sizeof(cache_set_t) * S);

    for (int sInd = 0; sInd < S; sInd++)
    {
        cache[sInd] = (cache_set_t)malloc(sizeof(cache_line_t) * E);

        for (int eInd = 0; eInd < E; eInd++)
        {
            cache[sInd][eInd].valid = '0';
            cache[sInd][eInd].tag = 0;
            cache[sInd][eInd].lru = 0;
        }
    }
}

/* do a load operation*/
void loadOp(mem_addr_t* addr)
{
    /*if cache hit
     *  hit_count++
     *else
     *  if cache is not full
     *    miss++
     *  else
     *    miss_count++
     *    eviction_count++
     */
    cache_set_t cset = cache[getSetBits(addr)];

    int i;
    int full = 1;
    int empty = 0; //keep track of the empty item
    int last = 0;  //keep track of the evict item
    unsigned long long int lru = cset[0].lru;

    for (i = 0; i < E; i++)
    {
        if ((cset[i]).valid == '1' &&
            getTagBits(addr) == (cset[i]).tag)
        {
            (cset[i]).lru = ++lru_counter;
            break;
        }

        else if ((cset[i]).valid == '0')
        {
            full = 0;
            empty = i;
        }

        else
        {
            if ((cset[i]).lru < lru)
            {
                last = i;
                lru = (cset[i]).lru;
            }
        }
    }

    if (i == E) // miss
    {
        miss_count++;

        if (full)   //evict
        {
            (cset[last]).tag = getTagBits(addr);
            (cset[last]).lru = ++lru_counter;
            eviction_count++;
        }

        else
        {
            (cset[empty]).valid = '1';
            (cset[empty]).tag = getTagBits(addr);
            (cset[empty]).lru = ++lru_counter;
        }
    }

    else //hit
    {
        hit_count++;
    }

}

/* do a store operation */
void storeOp(mem_addr_t* addr)
{
    /*if cache hit
     *  hit_count++
     *else
     *  do a load operation
     */
    cache_set_t cset = cache[getSetBits(addr)];
    int i;

    for (i = 0; i < E; i++)
    {
        if ((cset[i]).valid == '1' &&
            getTagBits(addr) == (cset[i]).tag)
        {
            (cset[i]).lru = ++lru_counter;
            break;
        }
    }

    if (i == E) //miss
    {
        loadOp(addr);
    }

    else //hit
    {
        hit_count++;
    }

}

/*do a modify operation */
void modifyOp(mem_addr_t* addr)
{
    /* do a load operation
     * do a store operation
     */
    loadOp(addr);
    storeOp(addr);
}

void accessData(mem_addr_t* addr, char* op)
{
    if (*op == 'L')
    {
        loadOp(addr);
    }

    if (*op == 'M')
    {
        modifyOp(addr);
    }

    if (*op == 'S')
    {
        storeOp(addr);
    }
}

/*
 * replayTrace - replays the given trace file against the cache
 *
 * YOU CAN RE-WRITE THIS FUNCTION IF YOU WANT TO.
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t* addr;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    char op[200];

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while( fgets(buf, 1000, trace_fp) != NULL)
    {
        sscanf(buf, "%s %p,%d", op, &addr, &len);
        accessData(addr,op);
    }

    fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    S = (1 << s);
    B = (1 << b);
    /* Initialize cache */
    initCache();

#ifdef DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif

    /* Read the trace and access the cache */
    replayTrace(trace_file);

    /* Free allocated memory */
    free(cache);

    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}


