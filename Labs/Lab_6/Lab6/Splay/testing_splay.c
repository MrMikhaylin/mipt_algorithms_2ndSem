#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Splay.h"

typedef struct TimePair TimePair;

struct TimePair
{
    double insertion;
    double deleting;
};

#define NAME_LENGHT  60
#define BLOCK_LENGHT 5

void run_splay_tests (const char* TestsPath, const char* ResultsPathInsertion, const char* ResultsPathDeleting, size_t from, size_t to, size_t step)
{
    assert ((TestsPath != NULL) && (ResultsPathInsertion != NULL) && (ResultsPathDeleting != NULL));
    
    char* filename_data = (char*) calloc (NAME_LENGHT, sizeof (char));                  // там лежат значения
    assert (filename_data != NULL);
    
    char* insertion_result = (char*) calloc (NAME_LENGHT, sizeof (char));               // запись результатов в среднем по пятерке в выходной файл
    assert (insertion_result != NULL);

    char* deleting_result = (char*) calloc (NAME_LENGHT, sizeof (char));                // запись результатов в среднем по пятерке в выходной файл
    assert (deleting_result != NULL);

    snprintf (insertion_result, NAME_LENGHT, "%s", ResultsPathInsertion);
    assert (insertion_result != NULL);
    
    snprintf (deleting_result, NAME_LENGHT, "%s", ResultsPathDeleting);
    assert (deleting_result != NULL);
    
    FILE* insert_result = fopen (insertion_result, "w");
    assert (insert_result != NULL);

    FILE* delete_result = fopen (deleting_result, "w");
    assert (delete_result != NULL);

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

    for (size_t i = from; i <= to; i += step)                             //перебор по всем размерам 
    {       
        for (size_t j = 0; j < BLOCK_LENGHT; j++)                         // перебор по каждой пятерке
        {
            snprintf (filename_data, NAME_LENGHT, "%s%zu_%zu", TestsPath, i, j);
    
            FILE* file_in = fopen (filename_data, "r");
            assert (file_in != NULL);

            fscanf (file_in, "%zu\n", &value);
            assert (value == i);

            SplayNode* tree = NULL;
            int* nums = (int*) calloc (value, sizeof (int));
            assert (nums != NULL);

            clock_t begin_insertion = clock ();

            int a = 0;

            for (int k = 0; k < i; k++)
            {
                fscanf (file_in, "%d ", &nums[k]);
                tree = insert_number (tree, nums[k]);

                if (tree->key == nums[k])
                    a++;
            }
            
            clock_t end_insertion = clock ();

            double insertion_time = (double) (end_insertion - begin_insertion) / CLOCKS_PER_SEC;

            clock_t begin_deleting = clock ();

            for (int k = 0; k < i/2; k++)
            {
                tree = delete (tree, nums, i);
            }

            clock_t end_deleting = clock ();

            double deleting_time = (double) (end_deleting - begin_deleting) / CLOCKS_PER_SEC;

            blocktime[blocktime_ind]->deleting = deleting_time;
            blocktime[blocktime_ind]->insertion = insertion_time;
            blocktime_ind++;

            memset (filename_data, '0', NAME_LENGHT);
            delete_tree (tree);
            free (nums);
            fclose (file_in);
        }

        for (size_t t = 0; t < BLOCK_LENGHT; t++)
        {
            average_insertion += blocktime[t]->insertion;
            average_deleting += blocktime[t]->deleting;
        }

        average_insertion /= BLOCK_LENGHT;
        average_deleting /= BLOCK_LENGHT;

        fprintf (insert_result, "%d %f\n", i, average_insertion);
        fprintf (delete_result, "%d %f\n", i, average_deleting);
        
        blocktime_ind = 0;
    }

    free (filename_data);
    free (insertion_result);
    free (deleting_result);

    for (int i = 0; i < BLOCK_LENGHT; i++)
    {
        free (blocktime[i]);
    }

    free (blocktime);

    fclose (insert_result);
    fclose (delete_result);
}

int main()
{
    run_splay_tests ("../tests/arrays/", "../results/insertion/Splay", "../results/deleting/Splay", 100000, 1000000, 100000);

    return 0;
}