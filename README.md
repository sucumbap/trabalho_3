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

Exercicio 4:
    Path: Trabalho_3/src/thread_pool/*
    Compile: make

    Consiste numa biblioteca de funções que implementam um pool de threads.
    Onde as tarefas não são executadas por uma thread especifica mas sim por uma thread que esteja disponivel.

Teste do Exercicio 4:
    Path: Trabalho_3/src/testing/pool.c && Trabalho_3/src/testing/pool.h
    Compile: make
    Run: ./bin/thread_pool_test <iterations> <min> <max> <nthreads> <queueDim>

    O programa realiza um teste do mecanismo de sincronismo thread_pool_t. Ele cria várias threads que operam operações aritmetricas ao acaso e as executa. Mantendo um olho para o estado atual da pool de threads, e o numero de threads que estão a executar tarefas.

    Exemplo:
        ./bin/thread_pool_test 10 10 50 14 100 
        Thread pool initialized with 14 threads and a queue size of 100
        Submitting task 0 to the thread pool
        Submitting task 1 to the thread pool
        Submitting task 2 to the thread pool
        Submitting task 3 to the thread pool
        Submitting task 4 to the thread pool
        Submitting task 5 to the thread pool
        Submitting task 6 to the thread pool
        Submitting task 7 to the thread pool
        Submitting task 8 to the thread pool
        Submitting task 9 to the thread pool
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread exiting
        Thread pool destroyed

Exercicio 5:
    Path: Trabalho_3/src/matrix/matrix.c && Trabalho_3/src/matrix/matrix.h && Trabalho_3/src/matrix/matrix_pool.c
    Compile: make
    Run: ./bin/matrix_test <rows M1> <columns M1> <rows M2> <columns M2> <nThreads>

    Consiste numa biblioteca de funções que operam sobre matrizes de inteiros.
    Requer a biblioteca do exercicio 4 para funcionar.
    Neste caso utiliza-se um pool de threads para realizar as operações de multiplicção sobre as matrizes.

Teste do Exercicio 5:

    Cria duas matrixes de interios com dimensões M1xM2 e M2xM3 e preenche-as com numeros aleatorios entre 0 e 999.
    Multiplica as duas matrizes e imprime o resultado.

    Exemplo:
        ./bin/matrix_test 10 10 10 10 10
        M1-> (10, 10)
        M2-> (10, 10)
        0383 0886 0777 0915 0793 0335 0386 0492 0649 0421 
        0362 0027 0690 0059 0763 0926 0540 0426 0172 0736 
        0211 0368 0567 0429 0782 0530 0862 0123 0067 0135 
        0929 0802 0022 0058 0069 0167 0393 0456 0011 0042 
        0229 0373 0421 0919 0784 0537 0198 0324 0315 0370 
        0413 0526 0091 0980 0956 0873 0862 0170 0996 0281 
        0305 0925 0084 0327 0336 0505 0846 0729 0313 0857 
        0124 0895 0582 0545 0814 0367 0434 0364 0043 0750 
        0087 0808 0276 0178 0788 0584 0403 0651 0754 0399 
        0932 0060 0676 0368 0739 0012 0226 0586 0094 0539 

        0795 0570 0434 0378 0467 0601 0097 0902 0317 0492 
        0652 0756 0301 0280 0286 0441 0865 0689 0444 0619 
        0440 0729 0031 0117 0097 0771 0481 0675 0709 0927 
        0567 0856 0497 0353 0586 0965 0306 0683 0219 0624 
        0528 0871 0732 0829 0503 0019 0270 0368 0708 0715 
        0340 0149 0796 0723 0618 0245 0846 0451 0921 0555 
        0379 0488 0764 0228 0841 0350 0193 0500 0034 0764 
        0124 0914 0987 0856 0743 0491 0227 0365 0859 0936 
        0432 0551 0437 0228 0275 0407 0474 0121 0858 0395 
        0029 0237 0235 0793 0818 0428 0143 0011 0928 0529 
        Waiting for threads to finish...
        Thread exiting
        Thread exiting
        .....
        Thread exiting

        Result-> (10, 10)
        ...


Exercicio 6:
