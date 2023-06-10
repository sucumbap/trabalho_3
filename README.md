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

    Exemplo (vector_size = 100, nthreads = 10):
       ./bin/vector_test 100 10
        Input: 811 84 335 925 358 718 40 404 888 41 753 244 54 902 158 965 249 925 697 529 219 788 875 228 75 660 971 143 747 177 213 22 229 384 324 760 170 294 9 541 199 528 769 788 514 628 76 81 633 716 426 465 56 993 707 868 520 532 175 59 780 311 472 798 743 512 466 928 601 350 828 426 109 620 387 433 90 173 765 867 352 877 490 278 451 316 824 479 827 468 754 321 402 596 296 370 446 154 83 406 
        Number of threads: 10
        Thread started, startIndex: 0, endIndex: 10
        Thread started, startIndex: 10, endIndex: 20
        Thread started, startIndex: 20, endIndex: 30
        Thread started, startIndex: 30, endIndex: 40
        Thread started, startIndex: 40, endIndex: 50
        Thread started, startIndex: 50, endIndex: 60
        Thread started, startIndex: 60, endIndex: 70
        Thread started, startIndex: 70, endIndex: 80
        Thread started, startIndex: 80, endIndex: 90
        Thread started, startIndex: 90, endIndex: 100
        Output: 993 ... 993 

Exercicio 3:
    Path: Trabalho_3/src/countdown/*
    Compile: make

    Consiste numa biblioteca de funções que criam um contdown para um conjunto de threads e as executa.
    Utiliza funçoes de biblioteca tipo pthread_mutex_lock e pthread_mutex_unlock para sincronizar as threads.
    Requer a biblioteca do exercicio 1 para funcionar.

Teste do Exercicio 3:
    Path: Trabalho_3/src/testing/countdown.c && Trabalho_3/src/testing/countdown.h
    Compile: make
    Run: ./bin/countdown_test <number_of_threads>

    O programa realiza um teste do mecanismo de sincronismo countdown_t. Ele cria várias threads que aguardam até que o valor do countdown alcance zero. Cada thread invoca a função countdown_wait para esperar, enquanto a thread principal usa countdown_down para decrementar o valor do countdown. Após a contagem regressiva, a thread principal aguarda a conclusão da thread criada com pthread_join e, em seguida, destrói a estrutura countdown_t usando countdown_destroy. O objetivo é demonstrar o uso do mecanismo de sincronismo countdown em um contexto de múltiplas threads.

    Exemplo:
        % ./bin/countdown_test 140
        Countdown down: 139
        Countdown down: 137
        Countdown down: 136
        .........
        Countdown down: 11
        Countdown down: 10
        Countdown down: 9
        Countdown down: 8
        Countdown down: 7
        Countdown down: 6
        Countdown down: 5
        Countdown down: 4
        Countdown down: 3
        Countdown down: 2
        Countdown down: 1
        Countdown down: 0
        Thread finished waiting.
