# trabalho_3 da UC Sistemas Operativos

Introdução:
    Este projeto consiste em várias funções com objetivos diferentes de modo a melhor entender o modo de funcionamento de tarefas e do seu sincronismo em POSIX.

Exercicio 1:
    Path: Trabalho_3/src/sot_barrier/*
    Compile: make

    Consiste numa barreira de threads em alternativa á pthread_barrier_t da biblioteca de PThreads.
    Utiliza mutex_locks e mutex_unlocks para esperar pelas threads que ainda não chegaram a barreira.

Teste do Exercicio 1:
    Path: Trabalho_3/src/testing/barrier.c && Trabalho_3/src/testing/barrier.h
    Compile: make
    Run: ./bin/barrier_test <number_of_threads>

    Consiste em codigo que cria nthreads e uma barrier, cada thread numerada entre 0 e nthreads -1, fazem operaçoes aritmetricas e ficam na barreira a espera até todas terem concluido.

    Exemplo (159 theads):
        .....
        Thread 53 reached the barrier
        Thread 151 reached the barrier
        Thread 136 reached the barrier
        Thread 155 reached the barrier
        Thread 149 reached the barrier      <-
        Thread 149 passed the barrier       <-
        Thread 51 passed the barrier
        Thread 37 passed the barrier
        Thread 52 passed the barrier
        .......
        *
        No momento em que a thread 149, que nesta iteração foi a ultima a chegar, todas as threads passem pela barreira logo a seguir.

Exercicio 2:
    Path: Trabalho_3/src/vector_utils/*
    Compile: make

    Consite numa biblioteca de funções que operam sobre vetores de inteiros.
    Requer a biblioteca do exercicio 1 para funcionar.
    Recebe um vetor de inteiros e o seu tamanho e o numero de threads que se pretende utilizar.
    Divide o vetor em partes iguais e cada thread fica responsavel por uma parte do vetor.




Teste do Exercicio 2:
    Path: Trabalho_3/src/testing/vector.c && Trabalho_3/src/testing/vector.h
    Compile: make
    Run: ./bin/vector_test <vector_size> <number_of_threads>

    Consiste em codigo que cria um vetor de tamanho vector_size e o preenche com numeros aleatorios entre 0 e 999.

    Exemplo (vector_size = 1000, nthreads = 10):
        .....
        Thread 0: 0 0 0 0 0 0 0 0 0 0
        Thread 1: 0 0 0 0 0 0 0 0 0 0
        Thread 2: 0 0 0 0 0 0 0 0 0 0
        Thread 3: 0 0 0 0 0 0 0 0 0 0
        Thread 4: 0 0 0 0 0 0 0 0 0 0
        Thread 5: 0 0 0 0 0 0 0 0 0 0
        Thread 6: 0 0 0 0 0 0 0 0 0 0
        Thread 7: 0 0 0 0 0 0 0 0 0 0
        Thread 8: 0 0 0 0 0 0 0 0 0 0
        Thread 9: 0 0 0 0 0 0 0 0 0 0
        .......
        *
        No momento em que a thread 9, que nesta iteração foi a ultima a chegar, todas as threads passem pela barreira logo a seguir.


        // to complete up

Exercicio 3: