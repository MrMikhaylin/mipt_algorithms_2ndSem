#ifndef _LINEAR_HEAP_H
#define _LINEAR_HEAP_H

#include <stddef.h>
#include "../common.h"

void sift_down (Heap* heap, size_t index, size_t num_of_children);

void linear_heap_constructor (int* array, size_t arr_length, size_t num_of_children);


#endif