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

/*
    function sot_barrier_init
    -------------------------
    this function initializes the barrier. It takes a pointer to a barrier struct and the number of threads to be expected.
    It initializes the mutex and condition variable. It returns 0 on success and -1 on failure.
*/
int sot_barrier_init(sot_barrier_t *barrier, int numberOfThreads);

/*
    function sot_barrier_destroy
    ----------------------------
    this function destroys the barrier. It takes a pointer to a barrier struct. It destroys the mutex and condition variable.
    It returns 0 on success and -1 on failure.
*/
int sot_barrier_destroy(sot_barrier_t *barrier);
/*
    function sot_barrier_wait
    -------------------------
    this function waits on the barrier. It takes a pointer to a barrier struct. It blocks until the number of threads waiting
    on the barrier equals the number of threads that the barrier was initialized with. It returns 0 on success and -1 on failure.
*/
int sot_barrier_wait(sot_barrier_t *barrier);