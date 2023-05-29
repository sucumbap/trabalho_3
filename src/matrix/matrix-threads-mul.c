#include "matrix.h"


void print_usage (char *binName)
{
    printf("\nusage: %s <rows M1> <columns M1> <rows M2> <columns M2> <nThreads>\n\n", binName);
}



int main (int argc, char *argv[]) {
	srand( time(NULL) );

    int nRows1    = 6;
    int nColumns1 = 4;
    int nRows2    = 4;
    int nColumns2 = 3;
    int nThreads  = 2;
    
    if ( argc < 4 ) {
        print_usage(argv[0]);
    }
    else {
        nRows1    = strtol(argv[1], NULL, 10);
        nColumns1 = strtol(argv[2], NULL, 10);
        nRows2    = strtol(argv[3], NULL, 10);
        nColumns2 = strtol(argv[4], NULL, 10);
        nThreads  = strtol(argv[5], NULL, 10);
    }
    
	printf("M1-> (%d, %d)\n", nRows1, nColumns1);
    printf("M2-> (%d, %d)\n", nRows2, nColumns2);

    Matrix *m1 = matrix_create(nRows1, nColumns1);
	matrix_set_random(m1);
	matrix_print(m1);
	
	Matrix *m2 = matrix_create(nRows2, nColumns2);
	matrix_set_random(m2);
	matrix_print(m2); 
	
	Matrix *result = matrix_multiplication_with_threads(m1, m2, nThreads);
    if (result == NULL) {
        fprintf(stderr, "Matrix multiplication error\n");
        exit(EXIT_FAILURE);
    }
	matrix_print(result); 

	matrix_destroy(m1);
	matrix_destroy(m2);
	matrix_destroy(result);
	
	return 0;
}
