#ifndef LOMUTO_PARTITION_H
#define LOMUTO_PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../common.h"

void lomuto_partition (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to)
{
    assert (array != NULL);
    
    int pivot = array[left + (right - left)/2];
    swap (&array[right], &array[left + (right - left)/2]);
    
    size_t i = left;
    
    for (int j = left; j <= right; ++j)
    {
        if (array[j] < pivot)
            swap (&array[i++], &array[j]);
    }

    swap (&(array[i]), &(array[right]));

    *equals_from = i;
    *equals_to = i;
}


#endif