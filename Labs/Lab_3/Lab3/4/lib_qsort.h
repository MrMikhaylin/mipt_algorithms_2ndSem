#ifndef LIB_QSORT_H
#define LIB_QSORT_H

#include <stddef.h>

int int_comparator (const void* first, const void* second);

void lib_qsort (int* array, size_t arr_length);

#endif