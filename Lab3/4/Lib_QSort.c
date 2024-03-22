#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Lib_QSort.h"

int comparator (const void* first, const void* second) 
{
    const int* a = (const int*) first;
    const int* b = (const int*) second;
    
    if (*a == *b)
        return 0;

    if (*a < *b)
        return -1;
    
    return 1;
}

void Lib_QSort (int* array, size_t arrlenght)
{
    assert (array != NULL);
    
    qsort (array, arrlenght, sizeof (int), comparator);
}