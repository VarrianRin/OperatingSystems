#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

struct monitor_type
{
    int* buffer;
    int  buf_size;
    int  fullness;
    int  cons_ptr;
    int  prod_ptr;
    int* volume;
    pthread_cond_t  empty;
    pthread_cond_t  full;
    pthread_mutex_t lock;
};

void *producer(void *number);

void *consumer(void* number);
