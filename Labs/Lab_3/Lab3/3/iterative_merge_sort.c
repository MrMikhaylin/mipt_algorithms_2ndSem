#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "iterative_merge_sort.h"
#include "../common.h"
 
int min (int x, int y)
{
    return (x < y) ? x : y; 
}

void iterative_merge_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    int* sec_array = (int*) calloc (arr_length, sizeof (int));
    assert (sec_array != NULL);

    size_t curr_size;
    size_t left;

    if (arr_length == 0)
        return;

    for (curr_size = 1; curr_size <= arr_length - 1; curr_size = 2 * curr_size)
    {
        for (left = 0; left < arr_length - 1; left += 2 * curr_size)
        {
            size_t mid_index = min (left + curr_size - 1, arr_length - 1);
 
            size_t right = min (left + 2 * curr_size - 1, arr_length - 1);
 
            get_merge (array, sec_array, left, right, mid_index);
        }
    }

    free (sec_array);
}