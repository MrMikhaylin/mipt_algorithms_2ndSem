#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Insertion_Sort.h"
#include "../Common.h"

void Insertion_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    for (size_t i = 1; i < arrlenght; i++)
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