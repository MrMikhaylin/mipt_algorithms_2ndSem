#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MSD_Sort.h"

void MSD_Sort (int *array, size_t arrlenght, size_t shift, int* buff)
{
    assert (array != NULL);
    assert (shift < 8*sizeof (int));

    if (arrlenght == 0)
        return;

    size_t pref_cnt[256] = {};

    for (size_t i = 0; i < arrlenght; i++)
        pref_cnt[(array[i] >> shift) & 0xff]++;

    for (size_t i = 1; i < 256; i++)
        pref_cnt[i] += pref_cnt[i - 1];

    for (size_t i = arrlenght; i; i--)
        buff[--pref_cnt[(array[i - 1] >> shift) & 0xff]] = array[i - 1];

    memcpy (array, buff, arrlenght*sizeof (int));

    if (shift == 0)
        return;

    for (size_t i = 0; i < 255; i++)
    {
        MSD_Sort (array + pref_cnt[i], pref_cnt[i + 1] - pref_cnt[i], shift - 8, buff);
    }
    
    MSD_Sort (array + pref_cnt[255], arrlenght - pref_cnt[255], shift - 8, buff);
}