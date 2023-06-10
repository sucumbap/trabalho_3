#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Work item function type
typedef void (wi_function_t)(void *);

// Work item structure for the queue
typedef struct {
    wi_function_t *function;
    void *args;
} work_t;
// Thread pool structure
// The queue is a circular buffer
// The queueLock is used to lock the queue
// The notify condition variable is used to notify threads that there is work to do
// The lock is used to lock the thread pool
// The threads array contains the threads
// The shutdown flag is used to tell the threads to exit
// The started flag is used to tell the threads that the thread pool has been started
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
// Initialize the thread pool
int threadpool_init (threadpool_t *tp, int queueDim, int nthreads);
// Submit a work item to the thread pool
int threadpool_submit (threadpool_t *tp, wi_function_t func, void *args);
// Destroy the thread pool
int threadpool_destroy (threadpool_t *tp);
// Thread function
void *threadpool_thread (void *threadpool);