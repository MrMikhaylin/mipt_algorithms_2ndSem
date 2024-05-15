#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void swap (int* value_a, int* value_b)
{
    assert ((value_a != NULL) && (value_b != NULL));

    int temporary = *value_a;
    *value_a = *value_b;
    *value_b = temporary;
}

size_t hoar_partition (int* array, size_t left, size_t right)
{
    assert (array != NULL);

    size_t piv_idx = left + (right - left)/2;
    int pivot = array[piv_idx];
    
    size_t ind_i = left;
    size_t ind_j = right;
    
    while (ind_i <= ind_j)
    {
        while (array[ind_i] < pivot)
        {
            ind_i++;
        }
        while (array[ind_j] > pivot)
        {
            ind_j--;
        }
        
        if (ind_i >= ind_j)
            return ind_j;
        
        swap (&array[ind_i++], &array[ind_j--]);
    }

    return ind_j;
}

void Sort (int* array, size_t left, size_t right)
{
    assert (array != NULL);
    
    if (&array[right] - &array[left] == 0)
        return;
    
    size_t pivot_index = hoar_partition (array, left, right);

    Sort (array, pivot_index + 1, right);
    Sort (array, left, pivot_index);
}

void data_in (int* array, size_t arrlength)
{
    assert (array != NULL);

    for (int i = 0; i < arrlength; i++)
    {
        scanf ("%d", &array[i]);
    }
}

void data_out (int* array, size_t arrlength)
{
    assert (array != NULL);

    for (int i = 0; i < arrlength; i++)
    {
        printf ("%d ", array[i]);
    }
}

int main()
{
    size_t N = 0;
    int control = scanf ("%zu", &N);
    if (!control)
    {
        printf ("Seek mistake in scanning array length\n");

        return 0;
    }

    int* data = (int*) calloc (N, sizeof (int));
    if (!data)
    {
        printf ("Seek mistake in memory allocation\n");

        return 0;
    }

    data_in (data, N);

    Sort (data, 0, N - 1);

    data_out (data, N);

    free (data);

    return 0;
}