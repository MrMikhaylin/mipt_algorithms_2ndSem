#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "bubble_sort.h"
#include "../common.h"

void bubble_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    bool WasSwaps = false;
    int x = 0;

    for (size_t n = 0; n < arr_length; n++)
    {
        for (size_t i = 0; i < arr_length - 1 - n; i++)
        {
            if (compare (array[i], array[i + 1]) > 0)
            {
                swap (&array[i], &array[i + 1]);
                WasSwaps = true;
            }
        }

        if (!WasSwaps)
            break;

        WasSwaps = false;
    }
}