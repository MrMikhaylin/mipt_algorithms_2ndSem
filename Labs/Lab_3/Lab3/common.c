#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "common.h"

int compare (int first, int second)
{
    if (first > second)
        return 1;
    
    if (first == second)
        return 0;

    return -1;    
}

void swap (int* first, int* second)
{
    assert (first != NULL);
    assert (second != NULL);

    int temp = 0;

    temp = *first;
    *first = *second;
    *second = temp;
}

void get_merge (int* array, int* sec_array, size_t left, size_t right, size_t mid_index)
{
    assert ((array != NULL) && (sec_array != NULL));

    size_t i = left;
    size_t j = mid_index + 1;
    size_t k = left;

    while ((i <= mid_index) && (j <= right))
    {
        if (array[i] > array[j])
            sec_array[k++] = array[j++];
        
        else
            sec_array[k++] = array[i++];
    }

    while (i <= mid_index)
    {
        sec_array[k++] = array[i++];
    }
    
    while (j <= right)
    { 
        sec_array[k++] = array[j++];
    }
    
    for (i = 0; i < right - left + 1; i++)
    { 
        array[left + i] = sec_array[left + i];
    }
}