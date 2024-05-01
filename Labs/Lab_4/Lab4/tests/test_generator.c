#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int* generate_array (size_t arr_length, int max_elem_size)
{
    int* array = (int*) calloc (arr_length, sizeof (int));
    assert (array != NULL);

    for (size_t i = 0; i < arr_length; i++)
    {
        array[i] = rand() % (max_elem_size + 1);
    }

    return array;
}

int main (int argc, char* argv[])
{
    size_t arr_length = (size_t) atoi (argv[1]);
    int max_elem_size = atoi (argv[2]);

    int rand = atoi (argv[3]);
    srand (rand);
    
    int* array = generate_array (arr_length, max_elem_size);
    assert (array != NULL);

    printf ("%zu\n", arr_length);

    for (size_t i = 0; i < arr_length; i++)
    {
        printf ("%d ", array[i]);
    }

    free (array);

    return 0;
}