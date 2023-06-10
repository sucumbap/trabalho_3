#include "sot_barrier.h"

int sot_barrier_init(sot_barrier_t *barrier, int numberOfThreads) {
    if(numberOfThreads <= 0){
        return -1;
    }
    // initialize barrier and its variables
    barrier->nThreads = numberOfThreads;
    barrier->nThreadsReceived = 0;

    if (pthread_mutex_init(&barrier->mutex, NULL) != 0) return -1; // error
    if (pthread_cond_init(&barrier->cond, NULL) != 0) {
        pthread_mutex_destroy(&barrier->mutex);
        return -1; // error
    }
    return 0;
}

int sot_barrier_destroy(sot_barrier_t *barrier) {
    // destroy mutex and condition variable
    if (pthread_mutex_destroy(&barrier->mutex) != 0) return -1; // error
    if (pthread_cond_destroy(&barrier->cond) != 0) return -1; // error
    return 0;
}

int sot_barrier_wait(sot_barrier_t *barrier) {
    // lock mutex
    pthread_mutex_lock(&barrier->mutex);
    // increment number of threads that have reached the barrier
    barrier->nThreadsReceived++;

    if(barrier->nThreadsReceived < barrier->nThreads) {
        // wait if not all threads have reached the barrier
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    } else {
        // broadcast(unlocks all threads currently blocked) if all threads have reached the barrier
        pthread_cond_broadcast(&barrier->cond);
    }
    // unlock mutex
    pthread_mutex_unlock(&barrier->mutex);
    return 0;
}