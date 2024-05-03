#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pivot.h"

size_t median (int* array, size_t left, size_t right, size_t temp)
{
    if (array[left] >= array[right])
    {
        if (array[right] >= array[temp])
            return right;
        
        if (array[temp] >= array[left])
            return left;
        
        return temp;
    }

    if (array[temp] >= array[right])
        return right;
        
    if (array[left] >= array[temp])
        return left;
        
    return temp;
}

size_t central (int* array, size_t left, size_t right)
{
    return left + (right - left)/2;
}

size_t arbitrary (int* array, size_t left, size_t right)
{
    return left + rand()%(right - left + 1);
}

size_t median_of_three (int* array, size_t left, size_t right)
{
    int temp = central (array, left, right);

    return median (array, left, right, temp);
}


size_t median_of_arbitrary (int* array, size_t left, size_t right)
{
    return median (array, arbitrary (array, left, right), arbitrary (array, left, right), arbitrary (array, left, right));
}