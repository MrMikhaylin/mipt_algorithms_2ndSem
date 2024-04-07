#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* generate_array (size_t arrlenght, int max_elem_size)
{
    int* array = (int*) calloc (arrlenght, sizeof (int));

    for (size_t i = 0; i < arrlenght; i++)
    {
        array[i] = rand() % (max_elem_size + 1);
    }

    return array;
}

int main (int argc, char* argv[])
{
    size_t arrlenght = (size_t) atoi (argv[1]);
    int max_elem_size = atoi (argv[2]);

    int rand = atoi (argv[3]);
    srand (rand);
    
    int* array = generate_array (arrlenght, max_elem_size);

    printf ("%zu\n", arrlenght);

    for (size_t i = 0; i < arrlenght; i++)
    {
        printf ("%d ", array[i]);
    }

    free (array);

    return 0;
}