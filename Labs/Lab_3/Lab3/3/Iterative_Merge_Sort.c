#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Iterative_Merge_Sort.h"
#include "../Common.h"
 
int min (int x, int y)
{
    return (x < y) ? x : y; 
}

void ItMerge_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    size_t curr_size;
    size_t left;

    if (arrlenght == 0)
        return;

    for (curr_size = 1; curr_size <= arrlenght - 1; curr_size = 2*curr_size)
    {
        for (left = 0; left < arrlenght - 1; left += 2*curr_size)
        {
            size_t mid_index = min (left + curr_size - 1, arrlenght - 1);
 
            size_t right = min (left + 2*curr_size - 1, arrlenght - 1);
 
            get_merge (array, left, right, mid_index);
        }
    }
}