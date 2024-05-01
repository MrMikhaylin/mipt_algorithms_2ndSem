#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "testing.h"
#include "./line/linear_heap.h"
#include "./insertion/insertion_heap.h"

int main ()
{
    run_tests ("./tests/heap_tests/", (void*) linear_heap_constructor, "./results/linear", 100000, 1000000, 100000);
    return 0;
}