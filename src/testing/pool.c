#include "pool.h"

int main() {
    threadpool_t tp;
    int queueDim = 500;

    int nthreads = 4;
    // Initialize the thread pool with the updated queue size
    if (threadpool_init(&tp, queueDim, nthreads) != 0) {
        fprintf(stderr, "Failed to initialize the thread pool.\n");
        return -1;
    }

    // Submit tasks to the thread pool in a loop
    for (int i = 0; i < ITERATIONS; i++) {
        char task_msg[10];
        sprintf(task_msg, "Task %d", i + 1);
        threadpool_submit(&tp, print_message, task_msg);
    }

    // Wait for the tasks to complete

    // Destroy the thread pool
    threadpool_destroy(&tp);

    return 0;
}

// Function to be executed by the worker threads
void print_message(void* message) {
    char* msg = (char*)message;
    for (int i = 0; i < ITERATIONS; i++) {
        printf("%s\n", msg);
    }
}