#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "LSD_Sort.h"

void LSD_Sort (int* array, size_t arrlenght)
{
    assert (array != NULL);
    
    if (arrlenght == 0)
        return;

    int* temp = (int*) calloc (arrlenght, sizeof (int));

    for (unsigned long long mask = 0xff, shift = 0; shift < 16; mask <<= 8, shift += 8)
    {
        int* pref_cnt = (int*) calloc (256, sizeof (int));
        memset (pref_cnt, 0, sizeof (pref_cnt));
        
        for (size_t i = 0 ; i < arrlenght ; i++)
        {
            pref_cnt[(array[i]&mask) >> shift]++;
        }

        for (size_t i = 1; i < 256; i++)
        {
            pref_cnt[i] += pref_cnt[i - 1];
        }
        
        for (int i = ((int) arrlenght) - 1; i >= 0 ; i--)
        {
            temp[--pref_cnt[(array[i]&mask) >> shift]] = array[i];
        }
        
        memcpy (array, temp, sizeof (int)*arrlenght);

        free (pref_cnt);
    }

    free (temp);
}