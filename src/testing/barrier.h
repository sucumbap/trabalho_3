#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sot_barrier/sot_barrier.h"

#define NUM_THREADS 20
#define NUM_ITERATIONS 1

sot_barrier_t barrier;
pthread_t threads[NUM_THREADS];

void* thread_function(void* arg);
