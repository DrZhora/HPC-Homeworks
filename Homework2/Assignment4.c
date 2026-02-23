#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_NUMBER 20000000
#define NUM_THREADS 4

typedef struct {
    int start;
    int end;
} ThreadData;


int is_prime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}


void* count_primes(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long* count = malloc(sizeof(long long));
    *count = 0;

    for (int i = data->start; i <= data->end; i++) {
        if (is_prime(i))
            (*count)++;
    }

    return count;
}

int main() {
    clock_t start, end;

    start = clock();

    long long seq_count = 0;
    for (int i = 1; i <= MAX_NUMBER; i++) {
        if (is_prime(i))
            seq_count++;
    }

    end = clock();
    double seq_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential prime count: %lld\n", seq_count);
    printf("Sequential time: %.3f seconds\n\n", seq_time);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    start = clock();

    int chunk = MAX_NUMBER / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk + 1;
        thread_data[i].end = (i == NUM_THREADS - 1) ?
                              MAX_NUMBER :
                              (i + 1) * chunk;

        pthread_create(&threads[i], NULL, count_primes, &thread_data[i]);
    }

    long long parallel_count = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        long long* partial;
        pthread_join(threads[i], (void**)&partial);
        parallel_count += *partial;
        free(partial);
    }

    end = clock();
    double parallel_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Parallel prime count: %lld\n", parallel_count);
    printf("Parallel time: %.3f seconds\n", parallel_time);

    return 0;
}