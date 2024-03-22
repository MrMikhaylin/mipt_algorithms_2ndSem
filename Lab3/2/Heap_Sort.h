#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stddef.h>

struct Heap
{
    int* data;
    size_t size;
};

void swap_node (struct Heap* heap, size_t parent, size_t index);

void sift_down (struct Heap* heap, size_t index, size_t k);

void Heap_Sort (int* array, size_t arrlenght, size_t k);


#endif