#include "matrix.h"

/**
 * matrix_create
 * 
 * Função para criar dinamicamente uma matriz com a dimensão de 
 * nRows x nColumns 
 * 
 * Devolve um ponteiro para a matriz criada ou NULL em caso de erro
 */
Matrix *matrix_create (int nRows, int nColumns) 
{
	Matrix *matrix = malloc(sizeof(Matrix));
	if ( matrix == NULL ) return NULL;
	
	matrix->nRows    = nRows;
	matrix->nColumns = nColumns;
	
	// support an empty matrix -> nRowns = 0
    if (nRows == 0) {
        matrix->values = NULL;
        return matrix;
    }

	matrix->values = (int **)malloc(nRows*sizeof(int *));
	
	if ( matrix->values == NULL ) {
		matrix->nRows = 0;  	 // set only for calling matrix_destroy
		matrix_destroy(matrix);
		return NULL;
	}
	
	for (int l = 0; l < nRows; ++l) {
		matrix->values[l] = malloc(nColumns * sizeof(int));
		
	    if ( matrix->values[l] == NULL ) {
			matrix->nRows = l;  	 // set only for calling matrix_destroy
			matrix_destroy(matrix);
			return NULL;
		}
	}
	
	return matrix;
}

/**
 * matrix_destroy
 * 
 * Elimina os recursos da matriz passada em argumento
 */
void matrix_destroy (Matrix *matrix)
{
	if (matrix == NULL) return;

	for (int l = 0; l < matrix->nRows; ++l) {
		free(matrix->values[l]);
	}
	free(matrix->values);
	free(matrix);
}


void matrix_set_random (Matrix *matrix)
{
	for (int l = 0; l < matrix->nRows; ++l) {
		for (int c = 0; c < matrix->nColumns; ++c) {
			matrix->values[l][c] = random()%1000;
		}
	}
}

void matrix_print (const Matrix *matrix)
{
	for (int l = 0; l < matrix->nRows; ++l) {
		for (int c = 0; c < matrix->nColumns; ++c) {
			printf("%04d ", matrix->values[l][c]);
		}
		printf("\n");
	}
}

/**
 * matrix_multiplication
 * 
 * Calcula o produto entre as matrizes m1 e m2. 
 * O numero de colunas de m1 tem de ser igual ao número de linhas de m2.
 * A matriz resultado tem o número de linhas de m1 e número de colunas de m2.
 * 
 * M1     -> m x n
 * M2     -> n x p
 * result -> m x p
 * 
 *                  n 
 * result[i, j] =   S   a[i, k]*b[k, j] 
 *                k = 0
 *             [ver https://en.wikipedia.org/wiki/Matrix_multiplication]
 * 
 * Devolve a matriz resultado ou NULL em caso de erro
 */
Matrix *matrix_multiplication (const Matrix *m1, const Matrix *m2)
{
	if (m1->nColumns != m2->nRows) return NULL;
	
	Matrix *result = matrix_create(m1->nRows, m2->nColumns);
	if ( result == NULL ) return NULL;
	
	for (int i = 0; i < result->nRows; ++i) {
		for (int j = 0; j < result->nColumns; ++j) {

			int sum = 0;
			for (int k = 0; k < m1->nColumns; ++k) {
				sum += m1->values[i][k] * m2->values[k][j];
			}
			result->values[i][j] = sum;
		}
	}
	return result;
}


void *sumTask(void *args) {
    TaskArgs *taskArgs = (TaskArgs *) args;
    Matrix *matrix = taskArgs->matrix;
    int rowIndex = taskArgs->rowIndex;

    // Calcular a soma dos elementos da linha
    int sum = 0;
    for (int c = 0; c < matrix->nColumns; ++c) {
        sum += matrix->values[rowIndex][c];
    }

    // Armazenar o resultado na estrutura de argumentos
    taskArgs->value = sum;

    pthread_exit(NULL);
}


void *matrix_multiply_thread(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->startRow; i < data->endRow; ++i) {
        for (int j = 0; j < data->result->nColumns; ++j) {
            int sum = 0;
            for (int k = 0; k < data->m1->nColumns; ++k) {
                sum += data->m1->values[i][k] * data->m2->values[k][j];
            }
            data->result->values[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

Matrix *matrix_multiplication_with_threads(Matrix *m1, Matrix *m2, int nThreads) {
    if (m1->nColumns != m2->nRows) return NULL;
    
    Matrix *result = matrix_create(m1->nRows, m2->nColumns);
    if (result == NULL) return NULL;

    pthread_t threads[nThreads];
    ThreadData threadData[nThreads];

    int rowsPerThread = result->nRows / nThreads;
    int extraRows = result->nRows % nThreads;
    int currentRow = 0;

    for (int i = 0; i < nThreads; ++i) {
        threadData[i].m1 = m1;
        threadData[i].m2 = m2;
        threadData[i].result = result;
        threadData[i].startRow = currentRow;

        int rows = rowsPerThread + (extraRows > 0 ? 1 : 0);
        threadData[i].endRow = currentRow + rows;

        currentRow += rows;
        extraRows--;

        pthread_create(&threads[i], NULL, matrix_multiply_thread, (void *)&threadData[i]);
    }

    for (int i = 0; i < nThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return result;
}

Matrix *matrix_multiplication_with_processes(Matrix *m1, Matrix *m2, int nProcesses) {
	if (m1->nColumns != m2->nRows) return NULL;

	Matrix *result = matrix_create(m1->nRows, m2->nColumns);
	if (result == NULL) return NULL;

	int rowsPerProcess = result->nRows / nProcesses;
	int extraRows = result->nRows % nProcesses;
	int currentRow = 0;

	for (int i = 0; i < nProcesses; ++i) {
		int rows = rowsPerProcess + (extraRows > 0 ? 1 : 0);
		extraRows--;

		pid_t pid = fork();
		if (pid == 0) {
			for (int i = currentRow; i < currentRow + rows; ++i) {
				for (int j = 0; j < result->nColumns; ++j) {
					int sum = 0;
					for (int k = 0; k < m1->nColumns; ++k) {
						sum += m1->values[i][k] * m2->values[k][j];
					}
					result->values[i][j] = sum;
				}
			}
			exit(0);
		}
		currentRow += rows;
	}

	for (int i = 0; i < nProcesses; ++i) {
		wait(NULL);
	}

	return result;
}
Matrix * matrix_multiplication_with_pool_threads (Matrix *m1, Matrix *m2,int nPartitions, threadpool_t *tp) {
	if (m1->nColumns != m2->nRows) return NULL;
	
	Matrix *result = matrix_create(m1->nRows, m2->nColumns);
	if (result == NULL) return NULL;

	int rowsPerThread = result->nRows / nPartitions;
	int extraRows = result->nRows % nPartitions;
	int currentRow = 0;

	for (int i = 0; i < nPartitions; ++i) {
		ThreadData *threadData = malloc(sizeof(ThreadData));
		threadData->m1 = m1;
		threadData->m2 = m2;
		threadData->result = result;
		threadData->startRow = currentRow;

		int rows = rowsPerThread + (extraRows > 0 ? 1 : 0);
		threadData->endRow = currentRow + rows;

		currentRow += rows;
		extraRows--;

		threadpool_submit(tp, matrix_multiply_thread, (void *)threadData);
	}

	threadpool_destroy(tp);

	return result;
}