#include "../sot_barrier/sot_barrier.h"

typedef struct {
    int size;
    int data[];
} vector;

typedef struct {
    int thread_count;
    int max_value;
    sot_barrier_t *barrier;
    vector *v;
} thread_data;

void find_larger_and_fill_parallel(int v[], int dim, int numberOfThreads);

void *find_larger_and_fill_parallel_thread(void *arg);