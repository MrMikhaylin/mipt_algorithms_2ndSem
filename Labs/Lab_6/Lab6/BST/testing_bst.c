#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "BST.h"

typedef struct TimePair TimePair;

struct TimePair
{
    double insertion;
    double deleting;
};

#define NAME_LENGHT  60
#define BLOCK_LENGHT 5

void run_bst_tests (const char* TestsPath, const char* ResultsPath, size_t arr_length)
{
    assert ((TestsPath != NULL) && (ResultsPath != NULL));
    
    char* filename_data = (char*) calloc (NAME_LENGHT, sizeof (char));                  // там лежат значения
    assert (filename_data != NULL);
    
    char* filename_result = (char*) calloc (NAME_LENGHT, sizeof (char));                // запись результатов в среднем по пятерке в выходной файл
    assert (filename_result != NULL);

    snprintf (filename_result, NAME_LENGHT, "%s", ResultsPath);
    assert (filename_result != NULL);
    
    FILE* result = fopen (filename_result, "w");
    assert (result != NULL);

    TimePair** blocktime = (TimePair**) calloc (BLOCK_LENGHT, sizeof (TimePair*));      //массив зн-ий времени для пятерки замеров
    assert (blocktime != NULL);

    for (int i = 0; i < BLOCK_LENGHT; i++)
    {
        blocktime[i] = (TimePair*) calloc (1, sizeof (TimePair));
    }

    int blocktime_ind = 0;

    int value = 0;

    double average_insertion = 0;
    double average_deleting = 0;
        
    for (size_t j = 0; j < BLOCK_LENGHT; j++)                                           // перебор по каждой пятерке
    {
        snprintf (filename_data, NAME_LENGHT, "%s%zu_%zu.sorted", TestsPath, arr_length, j);
    
        FILE* file_in = fopen (filename_data, "r");
        assert (file_in != NULL);

        fscanf (file_in, "%zu", &value);
        assert (value == arr_length);

        BSTNode* tree = NULL;

        clock_t begin_insertion = clock ();

        for (int i = 0; i < arr_length; i++)
        {
            fscanf (file_in, "%d ", &value);

            tree = insert_number (tree, value);
        }

        clock_t end_insertion = clock ();

        double insertion_time = (double) (end_insertion - begin_insertion) / CLOCKS_PER_SEC;

        clock_t begin_deleting = clock ();

        for (int i = 0; i < arr_length/2; i++)
        {    
            tree = delete_number (tree, tree->key);
        }

        clock_t end_deleting = clock ();

        double deleting_time = (double) (end_deleting - begin_deleting) / CLOCKS_PER_SEC;

        blocktime[blocktime_ind]->deleting = deleting_time;
        blocktime[blocktime_ind]->insertion = insertion_time;
        blocktime_ind++;

        memset (filename_data, '0', NAME_LENGHT);
        delete_tree (tree);    
        fclose (file_in);
    }

    for (size_t t = 0; t < BLOCK_LENGHT; t++)
    {
        average_insertion += blocktime[t]->insertion;
        average_deleting += blocktime[t]->deleting;
    }

    average_insertion /= BLOCK_LENGHT;
    average_deleting /= BLOCK_LENGHT;

    fprintf (result, "sorted:: %f %f\n", average_insertion, average_deleting);

    free (filename_data);
    free (filename_result);

    for (int i = 0; i < BLOCK_LENGHT; i++)
    {
        free (blocktime[i]);
    }

    free (blocktime);

    fclose (result);
}

int main()
{
    run_bst_tests ("../tests/arrays/", "./bst_sorted", 100000);

    return 0;
}