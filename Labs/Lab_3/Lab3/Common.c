#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Common.h"

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

void get_merge (int* array, size_t left, size_t right, size_t mid_index)
{
    assert (array != NULL);

    int* temp = (int*) calloc (right - left + 1, sizeof (int));
    assert (temp != NULL);

    size_t i = left;
    size_t j = mid_index + 1;
    size_t k = 0;

    while ((i <= mid_index) && (j <= right))
    {
        if (array[i] > array[j])
            temp[k++] = array[j++];
        
        else
            temp[k++] = array[i++];
    }

    while (i <= mid_index)
    {
        temp[k++] = array[i++];
    }
    
    while (j <= right)
    { 
        temp[k++] = array[j++];
    }
    
    for (i = 0; i < right - left + 1; i++)
    { 
        array[left + i] = temp[i];
    }

    free (temp);
}