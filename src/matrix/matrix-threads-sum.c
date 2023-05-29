#include "matrix.h"

int main(int argc, char *argv[]) {
	srand( time(NULL) );

    int nRows    = 6;
    int nColumns = 4;

    
    if ( argc < 3 ) {
        printf("\nUsage: %s <rows M1> <columns M1>\n\n", argv[0]);
    }
    else {
        nRows    = strtol(argv[1], NULL, 10);
        nColumns = strtol(argv[2], NULL, 10);
    }
    printf("M1-> (%d, %d)\n", nRows, nColumns);


    Matrix *matrix = matrix_create(nRows, nColumns);
    matrix_set_random(matrix);
    matrix_print(matrix);

    int numTasks = nRows;
    pthread_t *threads = malloc(numTasks * sizeof(pthread_t));
    TaskArgs *taskArgs = malloc(numTasks * sizeof(TaskArgs));

    for (int i = 0; i < numTasks; ++i) {
        taskArgs[i].matrix = matrix;
        taskArgs[i].rowIndex = i;
        pthread_create(&threads[i], NULL, sumTask, &taskArgs[i]);
    }

    for (int i = 0; i < numTasks; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Soma dos elementos de cada linha:\n");
    for (int i = 0; i < numTasks; ++i) {
        printf("Linha %d: %d\n", i, taskArgs[i].value);
    }

    free(threads);
    free(taskArgs);
    matrix_destroy(matrix);

    return 0;
}
