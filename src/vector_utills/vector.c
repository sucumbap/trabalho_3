#include "vector.h"

void find_larger_and_fill_parallel(int v[], int dim, int numberOfThreads) {
    int i;
    int max_value = v[0];
    vector *vector = malloc(sizeof(vector) + dim * sizeof(int));
    vector->size = dim;
    for(i = 0; i < dim; i++) {
        vector->data[i] = v[i];
    }

    sot_barrier_t barrier;
    sot_barrier_init(&barrier, numberOfThreads);

    pthread_t *threads = malloc(numberOfThreads * sizeof(pthread_t));
    thread_data *data = malloc(numberOfThreads * sizeof(thread_data));
    for(i = 0; i < numberOfThreads; i++) {
        data[i].thread_count = numberOfThreads;
        data[i].max_value = max_value;
        data[i].barrier = &barrier;
        data[i].v = vector;
        pthread_create(&threads[i], NULL, find_larger_and_fill_parallel_thread, &data[i]);
    }

    for(i = 0; i < numberOfThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    for(i = 0; i < dim; i++) {
        v[i] = vector->data[i];
    }

    free(vector);
    free(threads);
    free(data);
}

void *find_larger_and_fill_parallel_thread(void *arg) {
    thread_data *data = (thread_data *) arg;
    int thread_count = data->thread_count;
    int max_value = data->max_value;
    vector *v = data->v;
    int vector_size = v->size;
    sot_barrier_t *barrier = data->barrier;
    int i;

    for(i = 0; i < vector_size; i++) {
        if(v->data[i] > max_value) {
            max_value = v->data[i];
        }
    }
    sot_barrier_wait(barrier);

    return NULL;
}