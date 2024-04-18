#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "recursive_merge_sort.h"
#include "../common.h"

void merge_sort (int* array, int* sec_array, size_t left, size_t right)
{
    assert ((array != NULL) && (sec_array != NULL));

    if (left == right)
        return;

    if (right - left == 1)
    {
        if (compare (array[left], array[right]) > 0)
            swap (&array[left], &array[right]);
        
        return;
    }

    size_t mid_index = left + (right - left)/2;

    merge_sort (array, sec_array, left, mid_index);
    merge_sort (array, sec_array, mid_index + 1, right);

    get_merge (array, sec_array, left, right, mid_index);
}

void recursive_merge_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    if (arr_length == 0)
        return;

    size_t left = 0;
    size_t right = arr_length - 1;

    int* sec_array = (int*) calloc (arr_length, sizeof (int));
    assert (sec_array != NULL);

    merge_sort (array, sec_array, left, right);

    free (sec_array);
}