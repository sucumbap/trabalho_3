#include "vector.h"

int main( int argc, char *argv[] ) {
    if (argc < 2) {
        printf("Usage: %s <number of elements>\n", argv[0]);
        return 1;
    }
    if (atoi(argv[1]) < 1) {
        printf("The number of elements must be greater than 0\n");
        return 1;
    }

    int dim = atoi(argv[1]);
    int *values = malloc(dim * sizeof(int));


    srand(time(NULL));

    printf("Input: ");
    for (int i = 0; i < dim; i++) {
        values[i] = rand() % 1000; // Generate a random number from 0 to 999
        printf("%d ", values[i]);
    }
    printf("\n");

    find_larger_and_fill_parallel(values, dim, NTHREADS);

    printf("Output: ");
    for (int i = 0; i < dim; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    free(values);
    return 0;
}