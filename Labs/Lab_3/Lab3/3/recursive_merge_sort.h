#ifndef RECURSIVE_MERGE_SORT_H
#define RECURSIVE_MERGE_SORT_H

#include <stddef.h>

void merge_sort (int* array, int* sec_array, size_t left, size_t right);

void recursive_merge_sort (int* array, size_t arr_length);


#endif