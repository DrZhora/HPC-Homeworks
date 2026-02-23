#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

#define NUM_THREADS 4
#define ITERATIONS 2000000000UL

void* heavy_work(void* arg) {
    long id = (long)arg;

    unsigned long i;
    for (i = 0; i < ITERATIONS; i++) {

        if (i % 500000000UL == 0) {
            int cpu = sched_getcpu();
            printf("Thread %ld (pthread id %lu) running on CPU %d\n",
                   id,
                   (unsigned long)pthread_self(),
                   cpu);
        }
    }

    printf("Thread %ld finished\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, heavy_work, (void*)i) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed\n");
    return 0;
}