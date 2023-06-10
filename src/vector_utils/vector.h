#include "../sot_barrier/sot_barrier.h"

// define vector struct
// size is the number of elements in the vector
// data is the array of elements
typedef struct {
    int size;
    int data[];
} vector;

// define a struct to contain all the data needed by a thread
typedef struct {
    int thread_count;
    int max_value;
    sot_barrier_t *barrier;
    vector *v;
} thread_data;

// function find_larger_and_fill_parallel
// v is the vector to be filled
// dim is the number of elements in the vector
// numberOfThreads is the number of threads to be used
// this function finds the largest value in the vector and fills the vector with that value
void find_larger_and_fill_parallel(int v[], int dim, int numberOfThreads);

// function find_larger_and_fill_parallel_thread
// this function is the function that will be executed by each thread in the parallel version
void *find_larger_and_fill_parallel_thread(void *arg);