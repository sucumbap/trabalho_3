#include <stdio.h>
#include <pthread.h>
#include "../countdown/countdown.h"

#define NUM_THREADS 50

void* countdown_test(void* arg);