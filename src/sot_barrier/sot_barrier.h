#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
    struct sot_barrier_t
    --------------------
    This struct is used to implement a barrier. It contains a mutex and a condition variable.
    The mutex is used to protect the barrier's state. The condition variable is used to block
    threads until the barrier is reached. The barrier is reached when the number of threads
    waiting on the barrier equals the number of threads that the barrier was initialized with.
*/
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int nThreads;
    int nThreadsReceived;

} sot_barrier_t;


int sot_barrier_init    (sot_barrier_t *barrier, int numberOfThreads);

int sot_barrier_destroy (sot_barrier_t *barrier);

int sot_barrier_wait    (sot_barrier_t *barrier);