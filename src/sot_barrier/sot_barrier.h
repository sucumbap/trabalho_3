#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int nThreads;
    int nThreadsReceived;

} sot_barrier_t;


int sot_barrier_init    (sot_barrier_t *barrier, int numberOfThreads);

int sot_barrier_destroy (sot_barrier_t *barrier);

int sot_barrier_wait    (sot_barrier_t *barrier);