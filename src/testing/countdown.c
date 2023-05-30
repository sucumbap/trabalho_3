#include "countdown.h"

void* countdown_test(void* arg) {
    countdown_t* cd = (countdown_t*)arg;

    printf("Thread %lu started\n", (unsigned long)pthread_self());

    for (int i = 0; i < 1000000; i++) {
        int j = i * i;
        j--;
    }
    
    countdown_wait(cd);  // Wait until the countdown reaches zero
    
    printf("Thread %lu finished\n", (unsigned long)pthread_self());
    
    return NULL;
}

int main() {
    countdown_t cd;
    countdown_init(&cd, NUM_THREADS);

    pthread_t threads[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, countdown_test, &cd);
    }

    // Do some work before countdown
    
    countdown_down(&cd);  // Decrease the countdown value
    
    // Continue with other tasks before countdown
    
    countdown_down(&cd);  // Decrease the countdown value
    
    // Continue with other tasks before countdown
    
    countdown_down(&cd);  // Decrease the countdown value
    
    // Continue with other tasks before countdown
    
    countdown_down(&cd);  // Decrease the countdown value
    
    // Continue with other tasks before countdown
    
    countdown_down(&cd);  // Decrease the countdown value
    
    // Continue with other tasks before countdown
    
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    countdown_destroy(&cd);

    return 0;
}