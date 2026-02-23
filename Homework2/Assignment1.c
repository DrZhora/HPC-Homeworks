#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* thread_function(void* arg) {
    long thread_num = (long)arg;
    printf("Thread %ld is running (pthread id: %lu)\n",
           thread_num,
           (unsigned long)pthread_self());
    return NULL;
}

int main() {

    pthread_t threads[3];

    for (long i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void*)i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("All threads have finished execution\n");

    return 0;
}