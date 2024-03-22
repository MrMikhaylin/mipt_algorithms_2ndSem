#ifndef FLAG_PARTITION_H
#define FLAG_PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../Common.h"

void flag_partition (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to)
{
    assert (array != NULL);

    int pivot = array[left + (right - left)/2];
    size_t mid = left;
    
    while (mid <= right)
    {
        if (array[mid] < pivot)
            swap (&array[left++], &array[mid++]);
        
        else
            if (array[mid] == pivot)
                ++mid;
            
            else
                swap (&array[mid], &array[right--]);
    }

    *equals_from = left;
    *equals_to = right;
}


#endif