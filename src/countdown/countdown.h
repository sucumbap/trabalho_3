#include "../sot_barrier/sot_barrier.h"

// Countdown barrier
// This barrier is initialized with a value, and each thread that calls
// countdown_down() decrements the value. When the value reaches 0, all threads are released.
typedef struct { 
    int value; 
    sot_barrier_t barrier;
} countdown_t; 

// Initialize the countdown barrier with the given value
int countdown_init(countdown_t *cd, int initialValue); 
// Destroy the countdown barrier
int countdown_destroy(countdown_t *cd); 
// Wait for the countdown barrier to reach 0
int countdown_wait(countdown_t *cd); 
// Decrement the countdown barrier
int countdown_down(countdown_t *cd);