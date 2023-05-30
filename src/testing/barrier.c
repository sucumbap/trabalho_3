#include "barrier.h"

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        printf("Thread %d - Iteration %d\n", thread_id, i);
        sot_barrier_wait(&barrier);
        printf("Thread %d - Continuing\n", thread_id);
    }
    pthread_exit(NULL);
}

int main() {
    sot_barrier_init(&barrier, NUM_THREADS);

    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sot_barrier_destroy(&barrier);
    return 0;
}