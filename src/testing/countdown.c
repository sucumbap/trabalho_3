#include "countdown.h"

void* countdown_thread(void* arg) {
    countdown_t* cd = (countdown_t*)arg;
    countdown_wait(cd);
    printf("Thread finished waiting.\n");
    return NULL;
}

int main() {
    countdown_t cd;
    int initialValue = NUM_THREADS;
    int result = countdown_init(&cd, initialValue);
    if (result == -1) {
        printf("Countdown initialization failed.\n");
        return 1;
    }

    pthread_t thread;
    result = pthread_create(&thread, NULL, countdown_thread, (void*)&cd);
    if (result != 0) {
        printf("Failed to create thread.\n");
        return 1;
    }

    for (int i = 0; i < initialValue - 1; i++) {
        countdown_down(&cd);
        printf("Countdown down: %d\n", cd.value);
    }

    pthread_join(thread, NULL);
    
    result = countdown_destroy(&cd);
    if (result == -1) {
        printf("Countdown destruction failed.\n");
        return 1;
    }

    return 0;
}
