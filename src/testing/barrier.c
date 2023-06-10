#include "barrier.h"

int main(int argc, char** argv) {
    // number of threads to be created change this value to test the barrier
    int NUM_THREADS = 40;
    if (argc != 2) {
        printf("Usage: %s <number of threads>\n", argv[0]);
        return 1;
    } else {
        NUM_THREADS = atoi(argv[1]);
    }
    // array of threads to be created
    pthread_t threads[NUM_THREADS];

    int thread_ids[NUM_THREADS];
    int i;

    // Initialize the barrier
    if (sot_barrier_init(&barrier, NUM_THREADS) != 0) {
        printf("Failed to initialize barrier\n");
        return 1;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            printf("Failed to create thread %d\n", i);
            return 1;
        }
    }

    // Wait for threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the barrier
    if (sot_barrier_destroy(&barrier) != 0) {
        printf("Failed to destroy barrier\n");
        return 1;
    }

    return 0;
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    int result = 0;
    for (int i = 0; i < 100000000; i++) {
        result += i*i;
    }
    valueDump(result);

    printf("Thread %d reached the barrier\n", thread_id);
    sot_barrier_wait(&barrier);
    printf("Thread %d passed the barrier\n", thread_id);
        
    pthread_exit(NULL);
}
int valueDump(int value) {
    value = value - 5;
    return value;
}