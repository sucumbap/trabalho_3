#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../thread_pool/pool.h"

void print_message(void* message);
int generate_random_number(int min, int max);
void perform_arithmetic(void* args);
int valueDump(int value);