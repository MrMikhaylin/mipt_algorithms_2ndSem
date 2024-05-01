#ifndef _INSERTION_HEAP_H
#define _INSERTION_HEAP_H

#include <stddef.h>
#include "../common.h"

void sift_up (Heap* heap, size_t index, size_t num_of_children);

void insertion_heap_constructor (int* heap_array, size_t arr_length, size_t num_of_children);


#endif