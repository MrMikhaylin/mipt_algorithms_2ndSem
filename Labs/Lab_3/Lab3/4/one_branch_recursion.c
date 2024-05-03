#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "one_branch_recursion.h"

void one_branch_hoar  (int* array, const size_t ind_left, const size_t ind_right)
{
    assert (array != NULL);

    if (ind_left >= ind_right)
        return;
    
    size_t left  = ind_left;
    size_t right = ind_right;

    size_t equals_from = 0;
    size_t equals_to = 0;

    do
    {
        hoar_partition (array, left, right, &equals_from, &equals_to);

        size_t mid = equals_from;

        if (mid - left + 1 > right - mid)
        {
            one_branch_hoar (array, mid + 1, right);

            right = mid;
        }
        
        else
        {
            one_branch_hoar (array, left, mid);

            left = mid + 1;
        }

    } while (left < right);
}