#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Hoar_Partition.h"
#include "Flag_Partition.h"
#include "Lomuto_Partition.h"
#include "Quick_Sort.h"
#include "OneBranch_Recursion.h"

void QSort (int* array, size_t left, size_t right, void (*partition) (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to))
{
    assert (array != NULL);

    size_t equals_from = 0;
    size_t equals_to = 0;

    if (right - left <= 0)
        return;
    
    partition (array, left, right, &equals_from, &equals_to);

    QSort (array, left, equals_from, partition);
    
    if (equals_to + 1 <= right)
        QSort (array, equals_to + 1, right, partition);
}

void Quick_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);

    if (arrlenght == 0)
        return;

    size_t left = 0;
    size_t right = arrlenght - 1;
    
    QSort (array, left, right, hoar_partition);
    //OneBranch_Hoar (array, left, right);
}