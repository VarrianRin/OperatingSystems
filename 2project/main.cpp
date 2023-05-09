#include "2project_lib.h"

struct monitor_type monitor;

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "NO necessary input: <buffer size> <producers> <consumers>\n");
        exit(1);
    }

    int num_prod = atoi(argv[2]);
    int num_cons = atoi(argv[3]);
    srand(time(0));

    pthread_t* pid = (pthread_t*)calloc(num_prod, sizeof(pthread_t));
    pthread_t* cid = (pthread_t*)calloc(num_cons, sizeof(pthread_t));
    pthread_mutex_init(&monitor.lock, nullptr);
    pthread_cond_init(&monitor.full, nullptr);
    pthread_cond_init(&monitor.empty, nullptr);

    monitor.buf_size     = atoi(argv[1]);
    monitor.buffer       = (int*)calloc(monitor.buf_size, sizeof(int));
    monitor.fullness     = 0;
    monitor.volume       = (int*)calloc(num_cons, sizeof(int));

   for (int i = 0; i < num_prod; i++) {
       printf("Main: started producer %d\n", i);
       pthread_create(&pid[i], nullptr, producer, (void*) i);
   }
   for (int consume_size = num_prod * 2 * monitor.buf_size, i = 0; i < num_cons; i++) {
       printf("Main: started consumer %d\n", i);
       monitor.volume[i] = consume_size / num_cons + ((i + 1) / num_cons) * (consume_size % num_cons);
       pthread_create(&cid[i], nullptr, consumer, (void *) i);
   }

   for (int i = 0; i < num_prod; i++) {
       pthread_join(pid[i], nullptr);
       printf("Main: producer %d joined\n", i);
   }
   for (int i = 0; i < num_cons; i++) {
       printf("Main: consumer %d joined\n", i);
       pthread_join(cid[i], nullptr);
   }

   pthread_mutex_destroy(&monitor.lock);
   pthread_cond_destroy(&monitor.full);
   pthread_cond_destroy(&monitor.empty);
   free(monitor.buffer);
   free(monitor.volume);
   free(pid);
   free(cid);

   printf("Main: program completed\n");

   return 0;
}
