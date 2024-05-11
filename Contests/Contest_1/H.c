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

int hoar_partition (int* array, int l, int r)
{
    assert (array != NULL);

    int piv_idx = l + (r - l)/2;
    int pivot = array[piv_idx];
    
    int i = l;
    int j = r;
    
    while ( i <= j )
    {
        while (array[i] < pivot)
        {
            i++;
        }
        while (array[j] > pivot)
        {
            j--;
        }
        
        if (i >= j)
            return j;
        
        swap (&array[i++], &array[j--]);
    }

    return j;
}

void Sort (int* array, int left, int right)
{
    assert (array != NULL);
    
    if (&array[right] - &array[left] == 0)
        return;
    
    int pivot_index = hoar_partition (array, left, right);

    Sort (array, pivot_index + 1, right);
    Sort (array, left, pivot_index);
}

int main()
{
    int N = 0;
    scanf ("%d", &N);

    int* data = (int*) calloc (N, sizeof (int));
    assert (data != NULL);

    for (int i = 0; i < N; i++)
    {
        scanf ("%d", &data[i]);
    }

    Sort (data, 0, N - 1);

    for (int i = 0; i < N; i++)
    {
        printf ("%d ", data[i]);
    }

    free (data);

    return 0;
}