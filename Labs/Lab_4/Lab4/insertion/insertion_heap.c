#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "insertion_heap.h"

void sift_up (Heap* heap, size_t index, size_t num_of_children)
{
    while (index > 0)
    {
        int parent = (index - 1)/num_of_children;

        if (heap->data[parent] < heap->data[index])
        {
            swap (heap, parent, index);
            index = parent;
        }
    
        else
            return;
    }
}

void insertion_heap_constructor (int* heap_array, size_t arr_length, size_t num_of_children)
{
    assert (heap_array != NULL);

    Heap hp = {};

    Heap* heap = &hp;
    hp.data = heap_array;

    if (arr_length == 0)
        return;

    for (hp.size = 0; hp.size < arr_length; hp.size++)
    {
        sift_up (heap, hp.size, num_of_children);
    }

    hp.size++;
}