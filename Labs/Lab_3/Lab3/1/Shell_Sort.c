#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Shell_Sort.h"

void Shell_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);
    
    int step = 1;

    while (step <= (int) arrlenght/9)
    {
        step = step*3 + 1;
    }   
    
    for (; step > 0; step /= 3)
    {
        for (int i = step; i < (int) arrlenght; i += step)
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