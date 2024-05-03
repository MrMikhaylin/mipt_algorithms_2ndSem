#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MSD_sort.h"

void MSD_sort (int *array, size_t arr_length, size_t shift, int* buff)
{
    assert (array != NULL);
    assert (shift < 8*sizeof (int));

    if (arr_length == 0)
        return;

    size_t pref_cnt[256] = {};

    for (size_t i = 0; i < arr_length; i++)
        pref_cnt[(array[i] >> shift) & 0xff]++;

    for (size_t i = 1; i < 256; i++)
        pref_cnt[i] += pref_cnt[i - 1];

    for (size_t i = arr_length; i; i--)
        buff[--pref_cnt[(array[i - 1] >> shift) & 0xff]] = array[i - 1];

    memcpy (array, buff, arr_length*sizeof (int));

    if (shift == 0)
        return;

    for (size_t i = 0; i < 255; i++)
    {
        MSD_sort (array + pref_cnt[i], pref_cnt[i + 1] - pref_cnt[i], shift - 8, buff);
    }
    
    MSD_sort (array + pref_cnt[255], arr_length - pref_cnt[255], shift - 8, buff);
}