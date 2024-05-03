#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hoar_partition.h"
#include "flag_partition.h"
#include "lomuto_partition.h"
#include "quick_sort.h"
#include "one_branch_recursion.h"

void q_sort (int* array, size_t left, size_t right, void (*partition) (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to))
{
    assert (array != NULL);

    size_t equals_from = 0;
    size_t equals_to = 0;

    if (right - left <= 0)
        return;
    
    partition (array, left, right, &equals_from, &equals_to);

    q_sort (array, left, equals_from, partition);
    
    if (equals_to + 1 <= right)
        q_sort (array, equals_to + 1, right, partition);
}

void quick_sort (int* array, size_t arr_length)
{
    assert (array != NULL);

    if (arr_length == 0)
        return;

    size_t left = 0;
    size_t right = arr_length - 1;
    
    q_sort (array, left, right, hoar_partition);
}