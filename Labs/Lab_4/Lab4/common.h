#ifndef _COMMON_H
#define _COMMON_H

#include <stddef.h>

typedef struct Heap
{
    int* data;
    size_t size;
}Heap;

void swap (Heap* heap, size_t parent, size_t index);


#endif