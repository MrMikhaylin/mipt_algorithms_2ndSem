#ifndef PIVOT_H
#define PIVOT_H

#include <stddef.h>

size_t central (size_t left, size_t right);

size_t arbitrary (size_t left, size_t right);

size_t median_of_three (size_t left, size_t right);

size_t median_of_arbitrary (size_t left, size_t right);


#endif