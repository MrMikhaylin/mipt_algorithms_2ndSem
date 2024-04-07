#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

const double BILLION = 1000000000.0;

const size_t NAME_LENGHT = 120;
const size_t BLOCK_LENGHT = 5;

double* RunTests (const char* TestsPath, void* SortingFunction, const char* ResultsPath, size_t from, size_t to, size_t step)
{
    assert ((TestsPath != NULL) && (ResultsPath != NULL) && (SortingFunction != NULL));
    
    char* filename_in = (char*) calloc (NAME_LENGHT, sizeof (char)); // там лежат условия
    assert (filename_in != NULL);
    
    char* filename_out = (char*) calloc (NAME_LENGHT, sizeof (char)); //там лежат эталонные ответы
    assert (filename_out != NULL);
    
    char* filename_result = (char*) calloc (NAME_LENGHT, sizeof (char)); // запись результатов в среднем по каждой пятерке в выходной файл
    assert (filename_result != NULL);

    snprintf (filename_result, NAME_LENGHT, "%s", ResultsPath);
    assert (filename_result != NULL);
    
    FILE* result = fopen (filename_result, "w");
    assert (result != NULL);

    double* maintime = (double*) calloc ( (size_t) ((to - from)/step + 1), sizeof (double)); // массив средних значений времени для каждого размера
    int maintime_ind = 0;
    assert (maintime != NULL);

    double* blocktime = (double*) calloc (BLOCK_LENGHT, sizeof (double)); //массив зн-ий времени для пятерки замеров одного размера
    int blocktime_ind = 0;
    assert (blocktime != NULL);
    
    size_t arrlenght = 0; //размер массива сортировки
    int temp = 0;

    void (*Sort) (int*, size_t) = (void (*) (int*, size_t)) SortingFunction;

    for (size_t i = from; i <= to; i += step)  //перебор по всем размерам 
    {
        double average_time = 0;

        struct timespec start = {};
        struct timespec end = {};
        
        for (size_t j = 0; j < BLOCK_LENGHT; j++)  // перебор по каждой пятерке
        {
            snprintf (filename_in, NAME_LENGHT, "%s%zu_%zu.in", TestsPath, i, j);
            snprintf (filename_out, NAME_LENGHT, "%s%zu_%zu.out", TestsPath, i, j);

            FILE* file_in = fopen (filename_in, "r");
            FILE* file_out = fopen (filename_out, "r");
            assert ((file_in != NULL) && (file_out != NULL));

            fscanf (file_in, "%zu", &arrlenght);

            int* sorting_array = (int*) calloc (arrlenght, sizeof (int));
            assert (sorting_array != NULL);
            
            for (size_t m = 0; m < arrlenght; m++)
            {
                fscanf (file_in, "%d", &sorting_array[m]);
            }

            fscanf (file_out, "%d", &temp);

            if (arrlenght != (size_t) temp)
                assert (false);

            clock_gettime (CLOCK_REALTIME, &start);

            //int* buf = (int*) calloc (arrlenght, sizeof (int));

            Sort (sorting_array, arrlenght);

            //free (buf);

            clock_gettime (CLOCK_REALTIME, &end);

            blocktime[blocktime_ind++] = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / BILLION;  

            for (size_t k = 0; k < arrlenght; k++)
            {
                fscanf (file_out, "%d", &temp);
                
                if (sorting_array[k] != temp)
                    assert (false);
            }

            free (sorting_array);

            memset (filename_in, '0', NAME_LENGHT);
            memset (filename_out, '0', NAME_LENGHT);

            fclose (file_in);
            fclose (file_out);
        }

        for (size_t t = 0; t < BLOCK_LENGHT; t++)
        {
            average_time += blocktime[t];
        }

        average_time /= BLOCK_LENGHT;

        memset (blocktime, 0, BLOCK_LENGHT);
        blocktime_ind = 0;

        maintime[maintime_ind++] = average_time;

        fprintf (result, "%zu %f\n", i, average_time);
    }

    free (filename_in);
    free (filename_out);
    free (filename_result);

    free (blocktime);
    free (maintime);

    fclose (result);

    return maintime;
}


#endif