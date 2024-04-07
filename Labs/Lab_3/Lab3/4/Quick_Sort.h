#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>

void QSort (int* array, size_t left, size_t right, void (*partition) (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to));

void Quick_Sort (int* array, size_t arrlenght);


#endif