#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib_qsort.h"

int int_comparator (const void* first, const void* second) 
{
    return (*((const int*)first) > *((const int*)second)) - (*((const int*)second) > *((const int*)first));
}

void lib_qsort (int* array, size_t arr_length)
{
    assert (array != NULL);
    
    qsort (array, arr_length, sizeof (int), int_comparator);
}