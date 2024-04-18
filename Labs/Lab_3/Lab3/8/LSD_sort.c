#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MASK 0xff
#define PREF_ARR_SIZE 256
#define SHIFT_MAX 32
#define MASK_SH 8
#define SHIFT_DL 8

#include "LSD_sort.h"

void LSD_sort (int* array, size_t arr_length)
{
    assert (array != NULL);
    
    if (arr_length == 0)
        return;

    int* temp = (int*) calloc (arr_length, sizeof (int));
    assert (temp != NULL);

    for (unsigned long long mask = MASK, shift = 0; shift < SHIFT_MAX; mask <<= MASK_SH, shift += SHIFT_DL)
    {
        int* pref_cnt = (int*) calloc (PREF_ARR_SIZE, sizeof (int));
        assert (pref_cnt != NULL);
        
        memset (pref_cnt, 0, sizeof (pref_cnt));
        
        for (size_t i = 0 ; i < arr_length ; i++)
        {
            pref_cnt[(array[i]&mask) >> shift]++;
        }

        for (size_t i = 1; i < PREF_ARR_SIZE; i++)
        {
            pref_cnt[i] += pref_cnt[i - 1];
        }
        
        for (int i = ((int) arr_length) - 1; i >= 0 ; i--)
        {
            temp[--pref_cnt[(array[i]&mask) >> shift]] = array[i];
        }
        
        memcpy (array, temp, sizeof (int)*arr_length);

        free (pref_cnt);
    }

    free (temp);
}