#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shell_sort.h"

void shell_sort (int* array, size_t arr_length)
{
    assert (array != NULL);
    
    int step = 1;

    while (step <= (int) arr_length/9)
    {
        step = step * 3 + 1;
    }   
    
    for (; step > 0; step /= 3)
    {
        for (int i = step; i < (int) arr_length; i += step)
        {
            int j = i;
            int tmp = array[i];
            
            for (; j >= step && array[j - step] > tmp; j -= step)
            {
                array[j] = array[j - step];
            }
        
            array[j] = tmp;
        }
    }
}