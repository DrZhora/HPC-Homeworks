#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#define ARRAY_SIZE  50000000
#define NUM_THREADS 4

typedef struct {
    int *array;
    long start;
    long end;
    int local_max;
} ThreadArgs;


int sequential_max(int *arr, long size) {
    int max = INT_MIN;
    for (long i = 0; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void *thread_max(void *arg) {
    ThreadArgs *targ = (ThreadArgs *)arg;
    int max = INT_MIN;

    for (long i = targ->start; i < targ->end; i++) {
        if (targ->array[i] > max)
            max = targ->array[i];
    }

    targ->local_max = max;   
    return NULL;
}

static inline double elapsed_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec  - start.tv_sec)  * 1000.0 +
           (end.tv_nsec - start.tv_nsec) / 1e6;
}

int main(void) {
    printf("Allocating array of %d integers (~%.0f MB)...\n",
           ARRAY_SIZE, ARRAY_SIZE * sizeof(int) / 1e6);

    int *arr = malloc((long)ARRAY_SIZE * sizeof(int));
    if (!arr) { perror("malloc"); return 1; }

    srand(42);
    for (long i = 0; i < ARRAY_SIZE; i++)
        arr[i] = rand();

    printf("Array filled.\n\n");

    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    int seq_max = sequential_max(arr, ARRAY_SIZE);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double seq_ms = elapsed_ms(t0, t1);

    printf("=== Sequential ===\n");
    printf("  Maximum : %d\n", seq_max);
    printf("  Time    : %.3f ms\n\n", seq_ms);

    pthread_t      threads[NUM_THREADS];
    ThreadArgs     args[NUM_THREADS];
    long chunk = ARRAY_SIZE / NUM_THREADS;

    clock_gettime(CLOCK_MONOTONIC, &t0);

    for (int t = 0; t < NUM_THREADS; t++) {
        args[t].array     = arr;
        args[t].start     = t * chunk;
        args[t].end       = (t == NUM_THREADS - 1) ? ARRAY_SIZE : (t + 1) * chunk;
        args[t].local_max = INT_MIN;
        pthread_create(&threads[t], NULL, thread_max, &args[t]);
    }

    for (int t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    int par_max = INT_MIN;
    printf("=== Parallel (%d threads) ===\n", NUM_THREADS);
    for (int t = 0; t < NUM_THREADS; t++) {
        printf("  Thread %d local max: %d  (chunk [%ld, %ld))\n",
               t, args[t].local_max, args[t].start, args[t].end);
        if (args[t].local_max > par_max)
            par_max = args[t].local_max;
    }

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double par_ms = elapsed_ms(t0, t1);

    printf("\n  Global Maximum : %d\n", par_max);
    printf("  Time           : %.3f ms\n\n", par_ms);

    printf("=== Summary ===\n");
    printf("  Sequential : %d  (%.3f ms)\n", seq_max, seq_ms);
    printf("  Parallel   : %d  (%.3f ms)\n", par_max, par_ms);
    printf("  Results match: %s\n", seq_max == par_max ? "YES ✓" : "NO ✗");
    printf("  Speedup    : %.2fx\n", seq_ms / par_ms);

    free(arr);
    return 0;
}