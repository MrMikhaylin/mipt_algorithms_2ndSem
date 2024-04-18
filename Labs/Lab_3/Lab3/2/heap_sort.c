#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "heap_sort.h"

void swap_node (struct Heap* heap, size_t parent, size_t index)
{
    assert (heap != NULL);

    int temporary_value = heap->data[parent];
    heap->data[parent] = heap->data[index];
    heap->data[index] = temporary_value;
}

void sift_down (struct Heap* heap, size_t index, size_t k)
{
    assert (heap != NULL);

    size_t i_min = 0;

    while (index < heap->size)
    {
        i_min = index;

        for (size_t i = 1; i <= k; i++)
        {
            if ((index * k + i < heap->size) && (heap->data[index * k + i] > heap->data[i_min]))
                i_min = index*k + i;
        }
        
        if (heap->data[index] >= heap->data[i_min])
            break;

        swap_node (heap, index, i_min);
        index = i_min;
    }
}

void heap_sort (int* array, size_t arr_length, size_t k)
{
    assert (array != NULL);

    struct Heap hp = {};

    hp.size = arr_length;
    hp.data = array;

    struct Heap* heap = &hp;

    if (arr_length == 0)
        return;

    for (int index = ((int) arr_length) - 1; index >= 0; index--)
        sift_down (heap, (size_t) index, k);

    while (heap->size > 0)
    {
        swap_node (heap, 0, heap->size - 1);
        heap->size--;

        sift_down (heap, 0, k);
    }
}