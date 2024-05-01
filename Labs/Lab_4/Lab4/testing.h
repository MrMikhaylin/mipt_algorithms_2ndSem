#ifndef _TESTING_H
#define _TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

const double BILLION = 1000000000.0;

const size_t NAME_LENGHT = 120;

void run_tests (const char* TestsPath, void* HeapFunction, const char* ResultsPath, size_t from, size_t to, size_t step)
{
    assert ((TestsPath != NULL) && (ResultsPath != NULL) && (HeapFunction != NULL));
    
    char* filename_in = (char*) calloc (NAME_LENGHT, sizeof (char));
    assert (filename_in != NULL);
    
    char* filename_result = (char*) calloc (NAME_LENGHT, sizeof (char));
    assert (filename_result != NULL);

    snprintf (filename_result, NAME_LENGHT, "%s", ResultsPath);
    assert (filename_result != NULL);
    
    FILE* result = fopen (filename_result, "w");
    assert (result != NULL);
    
    size_t arr_length = 0;

    void (*heap_constructor) (int*, size_t, size_t) = (void (*) (int*, size_t, size_t)) HeapFunction;

    for (size_t i = from; i <= to; i += step)
    {
        snprintf (filename_in, NAME_LENGHT, "%s%zu.", TestsPath, i);
        FILE* file_in = fopen (filename_in, "r");
        assert (file_in != NULL);

        fscanf (file_in, "%zu\n", &arr_length);

        int* heap_array = (int*) calloc (arr_length, sizeof (int));
        assert (heap_array != NULL);
            
        for (size_t m = 0; m < arr_length; m++)
        {
            fscanf (file_in, "%d", &heap_array[m]);
        }

        clock_t begin = clock ();

        heap_constructor (heap_array, arr_length, 2);

        clock_t end = clock ();

        double time_point = (double) (end - begin)/CLOCKS_PER_SEC;

        free (heap_array);

        memset (filename_in, '0', NAME_LENGHT);

        fclose (file_in);

        fprintf (result, "%zu %f\n", i, time_point);
    }

    free (filename_in);
    free (filename_result);

    fclose (result);
}


#endif