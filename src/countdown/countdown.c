#include "countdown.h"

int countdown_init    (countdown_t *cd, int initialValue) {
    if(initialValue < 0) return -1; // error
    cd->value = initialValue;

    if (sot_barrier_init(&cd->barrier, initialValue) != 0) return -1; // error

    return 0;
}

int countdown_destroy (countdown_t *cd) {
    if (sot_barrier_destroy(&cd->barrier) != 0) return -1; // error
    return 0;
}

int countdown_wait(countdown_t *cd) {
    pthread_mutex_lock(&cd->barrier.mutex);
    cd->value--;

    if(cd->value > 0) {
        pthread_cond_wait(&cd->barrier.cond, &cd->barrier.mutex);
    } else {
        cd->value = 0;
        pthread_cond_broadcast(&cd->barrier.cond);
    }
    pthread_mutex_unlock(&cd->barrier.mutex);
    return 0;
}

int countdown_down(countdown_t *cd) {
    pthread_mutex_lock(&cd->barrier.mutex);
    cd->value--;
    pthread_mutex_unlock(&cd->barrier.mutex);
    return 0;
}
