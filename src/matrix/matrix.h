#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include "../thread_pool/pool.h"
/**
 * Matrix.h
 * 
 * Funções relacionadas com a manipulação de matrizes
 * 
 **/
#ifndef _MATRIX_H_
#define _MATRIX_H_



/**
 * Estrutura que representa uma matrix
 */
typedef struct 
{
	int nRows;
	int nColumns; 
	int **values;
} Matrix;

typedef struct {
    Matrix *matrix;
    int rowIndex;
    int value;
} TaskArgs;

typedef struct {
    Matrix *m1;
    Matrix *m2;
    Matrix *result;
    int startRow;
    int endRow;
} ThreadData;


Matrix *matrix_create         (int nRows, int nColumns);

void    matrix_destroy        (Matrix *matrix);

void    matrix_set_value      (Matrix *matrix, int value);

void    matrix_set_random     (Matrix *matrix);

void    matrix_print          (const Matrix *matrix);

Matrix *matrix_multiplication (const Matrix *m1, const Matrix *m2);

void *sumTask(void *args);

void *matrix_multiply_thread(void *arg);

void matrix_multiply_thread_wrapper(void* arg);

Matrix *matrix_multiplication_with_threads(Matrix *m1, Matrix *m2, int nThreads);

Matrix *matrix_multiplication_with_processes(Matrix *m1, Matrix *m2, int nProcesses);

Matrix * matrix_multiplication_with_pool_threads ( Matrix *m1, Matrix *m2, int nPartitions, threadpool_t *tp);

#endif
