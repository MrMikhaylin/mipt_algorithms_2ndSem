#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Bubble_Sort.h"
#include "../Common.h"

void Bubble_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    bool WasSwaps = false;
    int x = 0;

    for (size_t n = 0; n < arrlenght; n++)
    {
        for (size_t i = 0; i < arrlenght - 1 - n; i++)
        {
            if (compare (array[i], array[i+1]) > 0)
            {
                swap (&array[i], &array[i+1]);
                WasSwaps = true;
            }
        }

        if (!WasSwaps)
            break;

        WasSwaps = false;
    }
}