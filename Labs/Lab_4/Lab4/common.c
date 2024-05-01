#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"

void swap (Heap* heap, size_t parent, size_t index)
{
    assert (heap != NULL);

    int temporary_value = heap->data[parent];
    heap->data[parent] = heap->data[index];
    heap->data[index] = temporary_value;
}