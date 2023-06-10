#include "pool.h"
int ITERATIONS;


int main(int argc, char** argv) {
    if (argc != 6) {
        printf("Usage: %s <iterations> <min> <max> <nthreads> <queueDim>\n", argv[0]);
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        printf("Iterations must be a positive integer\n");
        return -1;
    }

    ITERATIONS = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    int queueDim = atoi(argv[5]);
    int nthreads = atoi(argv[4]);

    // Seed the random number generator
    srand(time(NULL));

    threadpool_t tp;
    

    // Initialize the thread pool with the updated queue size
    if (threadpool_init(&tp, queueDim, nthreads) != 0) {
        fprintf(stderr, "Failed to initialize the thread pool.\n");
        return -1;
    }
    printf("Thread pool initialized with %d threads and a queue size of %d\n", nthreads, queueDim);

    // Create an array to hold the range of random numbers
    int range[2] = { min, max };

    // Submit tasks to the thread pool in a loop
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Submitting task %d to the thread pool\n", i);
        threadpool_submit(&tp, perform_arithmetic, range);
    }

    // Wait for the tasks to complete
    while (tp.queueCount != 0);

    // Destroy the thread pool
    threadpool_destroy(&tp);
    printf("Thread pool destroyed\n");

    return 0;
}
int valueDump(int value) {
    value = value - 5;
    return value;
}

// Function to generate a random number between min and max (inclusive)
int generate_random_number(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// Function to be executed by the worker threads
void perform_arithmetic(void* args) {
    int* range = (int*)args;
    int min = range[0];
    int max = range[1];

    for (int i = 0; i < ITERATIONS; i++) {
        int num1 = generate_random_number(min, max);
        int num2 = generate_random_number(min, max);

        // Generate a random arithmetic operation (+, -, *, /)
        int operation = generate_random_number(0, 3);
        int result;

        switch (operation) {
            case 0:
                result = num1 + num2;
                valueDump(result);
                //printf("%d + %d = %d\n", num1, num2, result);
                break;
            case 1:
                result = num1 - num2;
                valueDump(result);
                //printf("%d - %d = %d\n", num1, num2, result);
                break;
            case 2:
                result = num1 * num2;
                valueDump(result);
                //printf("%d * %d = %d\n", num1, num2, result);
                break;
            case 3:
                if (num2 != 0) {
                    result = num1 / num2;
                    valueDump(result);
                    //printf("%d / %d = %d\n", num1, num2, result);
                }
                break;
        }
    }
}