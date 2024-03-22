#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Pivot.h"

size_t central (size_t left, size_t right)
{
    return left + (right - left)/2;
}

size_t arbitrary (size_t left, size_t right)
{
    return left + rand()%(right - left + 1);
}

size_t median_of_three (size_t left, size_t right)
{   
    return (central (left, right) + left + right)/3;
}

size_t median_of_arbitrary (size_t left, size_t right)
{
    return (arbitrary (left, right) + arbitrary (left, right) + arbitrary (left, right))/3;
}