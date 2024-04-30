#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib_qsort.h"

int int_comparator (const void* first, const void* second) 
{
    const int* a = (const int*) first;
    const int* b = (const int*) second;

    return (*a == *b) ? 0 : (*a < *b) ? -1 : 1;
}

void lib_qsort (int* array, size_t arr_length)
{
    assert (array != NULL);
    
    qsort (array, arr_length, sizeof (int), int_comparator);
}