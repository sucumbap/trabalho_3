#include "sot_barrier.h"

int sot_barrier_init    (sot_barrier_t *barrier, int numberOfThreads) {
    if(numberOfThreads <= 0) return -1; // error
    barrier->nThreads = numberOfThreads;
    barrier->nThreadsReceived = 0;

    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) return -1; // error
    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        pthread_mutex_destroy(&barrier->mutex);
        return -1; // error
    }
    return 0;
}

int sot_barrier_destroy (sot_barrier_t *barrier) {
    if (pthread_mutex_destroy(&barrier->mutex) != 0) return -1; // error
    if (pthread_cond_destroy(&barrier->cond) != 0) return -1; // error
    return 0;
}

int sot_barrier_wait    (sot_barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->nThreadsReceived++;

    if(barrier->nThreadsReceived < barrier->nThreads) {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    } else {
        barrier->nThreadsReceived = 0;
        pthread_cond_broadcast(&barrier->cond);
    }
    pthread_mutex_unlock(&barrier->mutex);
    return 0;
}