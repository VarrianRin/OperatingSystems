#include "2project_lib.h"

extern struct monitor_type monitor;

void *producer(void *number) {

    int id = (int) (long long int) number;
    printf("P%d: Producing %d values\n",  id, monitor.buf_size * 2);
    for (int i = 0; i < monitor.buf_size * 2; i++) {

        pthread_mutex_lock(&monitor.lock);

        while (monitor.fullness == monitor.buf_size) {

            printf("P%d: Blocked due to full buffer\n",  id);
            pthread_cond_wait(&monitor.full, &monitor.lock);
            printf("P%d: Done waiting on full buffer\n",  id);
        }

        int value = rand() % 11;
        monitor.buffer[monitor.prod_ptr] = value;
        printf("P%d: Writing %d to position %d\n",  id, value, monitor.prod_ptr);

        monitor.prod_ptr = (monitor.prod_ptr + 1) % monitor.buf_size;
        monitor.fullness++;

        pthread_cond_signal(&monitor.empty);
        pthread_mutex_unlock(&monitor.lock);
    }
    printf("P%d: Exiting\n",  id);
}

void *consumer(void* number) {

    int id = (int) (long long int) number;
    printf("C%d: Consuming %d values\n", id, monitor.volume[ id]);
    int value = 0;
    for (int i = 0; i < monitor.volume[ id]; i++) {
        pthread_mutex_lock(&monitor.lock);

        while (monitor.fullness == 0) {

            printf("C%d: Blocked due to empty buffer\n",id);
            pthread_cond_wait(&monitor.empty, &monitor.lock);
            if (monitor.fullness != monitor.buf_size)
                printf("C%d: Done waiting on empty buffer\n",  id);
        }

        value = monitor.buffer[monitor.cons_ptr];
        printf("C%d: Reading %d from position %d\n",  id, value, monitor.cons_ptr);

        monitor.cons_ptr = (monitor.cons_ptr + 1) % monitor.buf_size;
        monitor.fullness--;

        pthread_cond_signal(&monitor.full);
        pthread_mutex_unlock(&monitor.lock);
    }
    printf("C%d: Exiting\n",  id);
}