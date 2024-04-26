#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linear_heap.h"

void sift_down (Heap* heap, size_t index, size_t num_of_children)
{
    assert (heap != NULL);

    size_t i_min = 0;

    while (index < heap->size)
    {
        i_min = index;

        for (size_t i = 1; i <= num_of_children; i++)
        {
            if ((index * num_of_children + i < heap->size) && (heap->data[index * num_of_children + i] > heap->data[i_min]))
                i_min = index * num_of_children + i;
        }
        
        if (heap->data[index] >= heap->data[i_min])
            break;

        swap (heap, index, i_min);
        index = i_min;
    }
}

void linear_heap_constructor (int* array, size_t arr_length, size_t num_of_children)
{
    assert (array != NULL);

    Heap hp = {};

    hp.size = arr_length;
    hp.data = array;

    Heap* heap = &hp;

    if (arr_length == 0)
        return;

    for (int index = ((int) arr_length)/2 - 1; index >= 0; index--)
        sift_down (heap, (size_t) index, num_of_children);
}