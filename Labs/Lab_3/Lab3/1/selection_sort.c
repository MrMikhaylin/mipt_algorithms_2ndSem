#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "selection_sort.h"
#include "../common.h"

void selection_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    size_t ind_min = 0;
    int min = 0;

    if ((arr_length == 0) || (arr_length == 1))
        return;

    for (size_t i = 0; i < arr_length - 1; i++)
    {
        ind_min = i;

        for (size_t j = i + 1; j < arr_length; j++)
        {
            if (array[j] < array[ind_min])
                ind_min = j;
        }

        if (ind_min == i)
            continue;

        swap (&array[i], &array[ind_min]);
    }
}