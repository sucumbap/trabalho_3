#include "vector.h"


void find_larger_and_fill_parallel(int v[], int dim, int numberOfThreads) {
    int i;
    int max_value = INT_MIN;  // Initialize max_value with the smallest possible value
    vector *vec = malloc(sizeof(vector) + dim * sizeof(int));
    vec->size = dim;
    for (i = 0; i < dim; i++) {
        vec->data[i] = v[i];
    }

    int numThreads = (numberOfThreads > dim) ? dim : numberOfThreads; // Adjust the number of threads so numThreads <= dim
    printf("Number of threads: %d\n", numThreads);
    // Calculate the number of elements each thread should process
    int elementsPerThread = dim / numThreads;

    // Initialize the barrier
    sot_barrier_t barrier;
    sot_barrier_init(&barrier, numThreads);

    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    if (threads == NULL) {
        printf("Error allocating memory for threads\n");
        exit(1);
    }
    thread_data *data = malloc(numThreads * sizeof(thread_data));
    if (data == NULL) {
        printf("Error allocating memory for thread data\n");
        exit(1);
    }
    int startIndex = 0;
    for (i = 0; i < numThreads; i++) {
        // Set the start and end indices for each thread
        int endIndex = startIndex + elementsPerThread;
        if (i == numThreads - 1) {
            // The last thread should process any remaining elements
            endIndex = dim;
        }

        // Assign the data for each thread
        data[i].max_value = max_value;
        data[i].v = vec;
        data[i].barrier = &barrier;
        data[i].startIndex = startIndex;
        data[i].endIndex = endIndex;

        // Create the thread
        pthread_create(&threads[i], NULL, find_larger_and_fill_parallel_thread, &data[i]);

        // Update the start index for the next thread
        startIndex = endIndex;
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
    int startIndex = data->startIndex;
    int endIndex = data->endIndex;
    sot_barrier_t *barrier = data->barrier;
    int i;
    printf("Thread started, startIndex: %d, endIndex: %d\n", startIndex, endIndex);
    for (i = startIndex; i < endIndex; i++) {
        if (v->data[i] > max_value) {
            max_value = v->data[i];
        }
    }
    sot_barrier_wait(barrier);

    data->max_value = max_value;

    return NULL;
}