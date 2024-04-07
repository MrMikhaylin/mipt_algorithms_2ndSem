#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    size_t arrlenght = 0;
    scanf ("%zu", &arrlenght);

    int* array = (int*) calloc (arrlenght, sizeof (int));
    int size = 0;

    int temp = 0;

    while (scanf ("%d", &temp) == 1)
    {
        array[size] = temp;
        size++;
    }

    qsort (array, arrlenght, sizeof (int), comparator);

    printf ("%zu\n", arrlenght);

    for (size_t i = 0; i < arrlenght; i++)
    {
        printf ("%d ", array[i]);
    }

    free (array);

    return 0;
}