# trabalho_3 da UC Sistemas Operativos

Introdução:
    Este projeto consiste em várias funções com objetivos diferentes de modo a melhor entender o modo de funcionamento de tarefas e do seu sincronismo em POSIX.

Exercio 1:
    Path: Trabalho_3/src/sot_barrier/...
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
        Thread 149 reached the barrier      *
        Thread 149 passed the barrier       *
        Thread 51 passed the barrier
        Thread 37 passed the barrier
        Thread 52 passed the barrier
        .......
        *
        No momento em que a thread 149, que nesta iteração foi a ultima a chegar, todas as threads passem pela barreira logo a seguir.


