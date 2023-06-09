#include "pool.h"

int threadpool_init(threadpool_t *tp, int queueDim, int nthreads) {
    // Initialize the thread pool
    tp->queueSize = queueDim;
    tp->nthreads = nthreads;
    tp->queue = (work_t *) malloc(queueDim * sizeof(work_t));
    tp->queueHead = 0;
    tp->queueTail = 0;
    tp->queueCount = 0;
    tp->threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
    tp->shutdown = 0;
    tp->started = 0;
    if (tp->queue == NULL || tp->threads == NULL) {
        perror("malloc");
        return -1;
    }
    // Initialize the thread pool lock
    if (pthread_mutex_init(&(tp->lock), NULL) != 0) {
        perror("pthread_mutex_init");
        return -1;
    }
    // Initialize the queue lock
    if (pthread_mutex_init(&(tp->queueLock), NULL) != 0) {
        perror("pthread_mutex_init");
        return -1;
    }
    // Initialize the notify condition variable
    if (pthread_cond_init(&(tp->notify), NULL) != 0) {
        perror("pthread_cond_init");
        return -1;
    }
    // Create the threads
    for (int i = 0; i < nthreads; i++) {
        if (pthread_create(&(tp->threads[i]), NULL, threadpool_thread, (void *) tp) != 0) {
            perror("pthread_create");
            return -1;
        }
        tp->started++;
    }
    return 0;
}

void *threadpool_thread(void *threadpool) {
    // Thread function
    threadpool_t *tp = (threadpool_t *) threadpool;
    work_t work;

    while (1) {
        // Lock must be taken to wait on conditional variable
        pthread_mutex_lock(&(tp->lock));
        // Wait on condition variable, check for spurious wakeups
        while (tp->queueCount == 0 && !tp->shutdown) {
            pthread_cond_wait(&(tp->notify), &(tp->lock));
        }
        // Shutdown will exit the thread
        if (tp->shutdown) {
            pthread_mutex_unlock(&(tp->lock));
            break;
        }
        // Grab our task from the queue
        pthread_mutex_lock(&(tp->queueLock));
        work.function = tp->queue[tp->queueHead].function;
        work.args = tp->queue[tp->queueHead].args;
        tp->queueHead = (tp->queueHead + 1) % tp->queueSize;
        tp->queueCount--;
        // Unlock queue and thread pool
        pthread_mutex_unlock(&(tp->queueLock));
        pthread_mutex_unlock(&(tp->lock));

        (*(work.function))(work.args);

        free(work.args); // Free the memory allocated for task arguments
    }
    // Remove thread from the pool and exit and notify the main thread
    tp->started--;
    printf("Thread exiting\n");
    pthread_exit(NULL);
    return NULL;
}

int threadpool_submit(threadpool_t *tp, wi_function_t func, void *args) {
    // lock the queue
    pthread_mutex_lock(&(tp->queueLock));

    if (tp->queueCount == tp->queueSize) {
        pthread_mutex_unlock(&(tp->queueLock));
        return -1;
    }
    // Add task to the queue
    tp->queue[tp->queueTail].function = func;

    // Allocate memory for task arguments and copy the content
    tp->queue[tp->queueTail].args = malloc(sizeof(void*));
    memcpy(tp->queue[tp->queueTail].args, args, sizeof(void*));
    // Increment queue tail
    tp->queueTail = (tp->queueTail + 1) % tp->queueSize;
    tp->queueCount++;
    // Unlock the queue
    pthread_cond_signal(&(tp->notify));
    pthread_mutex_unlock(&(tp->queueLock));

    return 0;
}

int threadpool_destroy(threadpool_t *tp) {
    pthread_mutex_lock(&(tp->lock));

    if (tp->shutdown) {
        pthread_mutex_unlock(&(tp->lock));
        return -1;
    }

    tp->shutdown = 1;
    // unlock the thread pool, all the threads will exit
    pthread_mutex_unlock(&(tp->lock));
    pthread_cond_broadcast(&(tp->notify));

    for (int i = 0; i < tp->started; i++) {
        pthread_join(tp->threads[i], NULL);
    }
    // Free allocated memory
    free(tp->threads);
    free(tp->queue);
    // Destroy mutex and condition variable
    pthread_mutex_destroy(&(tp->lock));
    pthread_mutex_destroy(&(tp->queueLock));
    pthread_cond_destroy(&(tp->notify));

    return 0;
}
