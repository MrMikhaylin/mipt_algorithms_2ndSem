#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Selection_Sort.h"
#include "../Common.h"

void Selection_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    size_t ind_min = 0;
    int min = 0;

    if ((arrlenght == 0) || (arrlenght == 1))
        return;

    for (size_t i = 0; i < arrlenght - 1; i++)
    {
        ind_min = i;

        for (size_t j = i + 1; j < arrlenght; j++)
        {
            if (array[j] < array[ind_min])
                ind_min = j;
        }

        if (ind_min == i)
            continue;

        swap (&array[i], &array[ind_min]);
    }
}

/*void SelectionSort(int* arr, size_t size)
{
    int min = INT_MAX, temp = 0;
    for(size_t i = 0; i < size - 1; i++)
    {
        min = i;

        for (size_t j = i + 1; j < size; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (min == i) continue;
        temp     = arr[i];
        arr[i]   = arr[min];
        arr[min] = temp;
    }
}*/