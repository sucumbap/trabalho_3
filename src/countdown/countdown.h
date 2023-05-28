#include "../sot_barrier/sot_barrier.h"

typedef struct { 
    int value; 
    sot_barrier_t barrier;
} countdown_t; 
 
int countdown_init(countdown_t *cd, int initialValue); 
int countdown_destroy(countdown_t *cd); 
int countdown_wait(countdown_t *cd); 
int countdown_down(countdown_t *cd);