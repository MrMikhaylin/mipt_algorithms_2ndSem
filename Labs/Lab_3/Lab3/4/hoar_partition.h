#ifndef HOAR_PARTITION_H
#define HOAR_PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../common.h"
#include "../5/pivot.h"

void hoar_partition (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to)
{
    assert (array != NULL);
    
    size_t piv_idx = central (array, left, right);
    int pivot = array[piv_idx];
    
    size_t i = left;
    size_t j = right;
    
    while (i <= j)
    {
        while (array[i] < pivot)
        {
            i++;
        }

        while (array[j] > pivot)
        {
            j--;
        }
        
        if (i >= j)
            break;
        
        swap (&array[i++], &array[j--]);
    }

    *equals_from = j;
    *equals_to = j;
}


#endif