#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../sot_barrier/sot_barrier.h"

// barrier to be used
sot_barrier_t barrier;

// function thread that will execute
// the barrier will be reached when all threads have finished their computation
// simple arithemtic computation res *= i*i
void* thread_function(void* arg);

// simple function to dump a value, avoid compiler optimization warning
int valueDump(int value);