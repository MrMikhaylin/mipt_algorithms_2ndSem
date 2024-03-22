#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Recursive_Merge_Sort.h"
#include "../Common.h"

void merge_sort (int* array, size_t left, size_t right)
{
    assert (array != NULL);

    if (left == right)
        return;

    if (right - left == 1)
    {
        if (compare (array[left], array[right]) > 0)
            swap (&array[left], &array[right]);
        
        return;
    }

    size_t mid_index = left + (right - left)/2;

    merge_sort (array, left, mid_index);
    merge_sort (array, mid_index + 1, right);

    get_merge (array, left, right, mid_index);
}

void RecMerge_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    if (arrlenght == 0)
        return;

    size_t left = 0;
    size_t right = arrlenght - 1;

    merge_sort (array, left, right);
}
