#ifndef LIB_QSORT_H
#define LIB_QSORT_H

#include <stddef.h>

int comparator (const void* first, const void* second);

void Lib_QSort (int* array, size_t arrlenght);

#endif