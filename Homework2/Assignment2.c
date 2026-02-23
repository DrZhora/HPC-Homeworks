#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 50000000
#define NUM_THREADS 4

int *array;

typedef struct {
    int start;
    int end;
} ThreadData;


void* partial_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long* sum = malloc(sizeof(long long));
    *sum = 0;

    for (int i = data->start; i < data->end; i++) {
        *sum += array[i];
    }

    return sum;
}

int main() {
    array = malloc(sizeof(int) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 10;
    }

    // ---------------- Sequential ----------------
    clock_t start = clock();

    long long seq_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        seq_sum += array[i];
    }

    clock_t end = clock();
    double seq_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential sum: %lld\n", seq_sum);
    printf("Sequential time: %.3f seconds\n\n", seq_time);

    // ---------------- Parallel ----------------
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    start = clock();

    int chunk = ARRAY_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == NUM_THREADS - 1) ?
                              ARRAY_SIZE :
                              (i + 1) * chunk;

        pthread_create(&threads[i], NULL, partial_sum, &thread_data[i]);
    }

    long long parallel_sum = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        long long* partial;
        pthread_join(threads[i], (void**)&partial);
        parallel_sum += *partial;
        free(partial);
    }

    end = clock();
    double parallel_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Parallel sum: %lld\n", parallel_sum);
    printf("Parallel time: %.3f seconds\n", parallel_time);

    free(array);
    return 0;
}