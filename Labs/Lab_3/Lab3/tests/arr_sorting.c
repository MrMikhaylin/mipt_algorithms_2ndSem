#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int int_comparator (const void* first, const void* second)
{
    const int* a = (const int*) first;
    const int* b = (const int*) second;
    
    if (*a == *b)
        return 0;

    if (*a < *b)
        return -1;
    
    return 1;
}

int main()
{
    size_t arr_length = 0;
    assert (scanf ("%zu", &arr_length) != NULL);

    int* array = (int*) calloc (arr_length, sizeof (int));
    assert (array != NULL);

    int size = 0;

    int temp = 0;

    while (scanf ("%d", &temp) == 1)
    {
        array[size] = temp;
        size++;
    }

    qsort (array, arr_length, sizeof (int), int_comparator);

    printf ("%zu\n", arr_length);

    for (size_t i = 0; i < arr_length; i++)
    {
        printf ("%d ", array[i]);
    }

    free (array);

    return 0;
}