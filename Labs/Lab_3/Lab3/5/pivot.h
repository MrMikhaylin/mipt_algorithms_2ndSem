#ifndef PIVOT_H
#define PIVOT_H

#include <stddef.h>

size_t median (int* array, size_t left, size_t right, size_t temp);

size_t central (int* array, size_t left, size_t right);

size_t arbitrary (int* array, size_t left, size_t right);

size_t median_of_three (int* array, size_t left, size_t right);

size_t median_of_arbitrary (int* array, size_t left, size_t right);


#endif