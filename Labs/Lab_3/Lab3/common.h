#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

int compare (int first, int second);

void swap (int* first, int* second);

void get_merge (int* array, int* sec_array, size_t left, size_t right, size_t mid_index);


#endif