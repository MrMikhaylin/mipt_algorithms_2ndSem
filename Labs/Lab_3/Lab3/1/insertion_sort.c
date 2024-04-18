#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "insertion_sort.h"
#include "../common.h"

void insertion_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    for (size_t i = 1; i < arr_length; i++)
    {
        size_t temp = i;

        for (int j = (int) i - 1; j >= 0; j--)
        {
            if (compare (array[i], array[j]) >= 0)
                break;
            
            swap (&(array[i]), &(array[j]));
            i--;
        }

        i = temp;
    }
}