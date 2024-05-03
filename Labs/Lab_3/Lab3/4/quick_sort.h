#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>

void q_sort (int* array, size_t left, size_t right, void (*partition) (int* array, size_t left, size_t right, size_t* equals_from, size_t* equals_to));

void quick_sort (int* array, size_t arr_length);


#endif