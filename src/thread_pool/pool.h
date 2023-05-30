#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (wi_function_t)(void *);

typedef struct {
    wi_function_t *function;
    void *args;
} work_t;
typedef struct {
    pthread_mutex_t lock;
    pthread_mutex_t queueLock;
    pthread_cond_t notify;
    pthread_t *threads;
    work_t *queue;
    int queueSize;
    int queueHead;
    int queueTail;
    int queueCount;
    int nthreads;
    int shutdown;
    int started;
} threadpool_t;

int threadpool_init (threadpool_t *tp, int queueDim, int nthreads);
int threadpool_submit (threadpool_t *tp, wi_function_t func, void *args);
int threadpool_destroy (threadpool_t *tp);
void *threadpool_thread (void *threadpool);