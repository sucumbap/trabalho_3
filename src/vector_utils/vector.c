#include "vector.h"
#include <limits.h>

void find_larger_and_fill_parallel(int v[], int dim, int numberOfThreads) {
    int i;
    int max_value = INT_MIN;  // Initialize max_value with the smallest possible value
    vector *vec = malloc(sizeof(vector) + dim * sizeof(int));
    vec->size = dim;
    for (i = 0; i < dim; i++) {
        vec->data[i] = v[i];
    }

    int numThreads = (numberOfThreads > dim) ? dim : numberOfThreads; // Adjust the number of threads
    sot_barrier_t barrier;
    sot_barrier_init(&barrier, numThreads);

    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    thread_data *data = malloc(numThreads * sizeof(thread_data));
    for (i = 0; i < numThreads; i++) {
        data[i].max_value = max_value;
        data[i].v = vec;
        data[i].barrier = &barrier;
        pthread_create(&threads[i], NULL, find_larger_and_fill_parallel_thread, &data[i]);
    }

    for (i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    max_value = vec->data[0];
    for (i = 1; i < dim; i++) {
        if (vec->data[i] > max_value) {
            max_value = vec->data[i];
        }
    }

    for (i = 0; i < dim; i++) {
        v[i] = max_value;
    }
    free(vec);
    free(threads);
    free(data);
}

void *find_larger_and_fill_parallel_thread(void *arg) {
    thread_data *data = (thread_data *)arg;
    int max_value = data->max_value;
    vector *v = data->v;
    int vector_size = v->size;
    sot_barrier_t *barrier = data->barrier;
    int i;

    for (i = 0; i < vector_size; i++) {
        if (v->data[i] > max_value) {
            max_value = v->data[i];
        }
    }
    sot_barrier_wait(barrier);

    data->max_value = max_value;

    return NULL;
}
