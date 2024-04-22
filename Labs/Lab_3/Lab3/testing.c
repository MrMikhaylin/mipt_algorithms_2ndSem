#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "testing.h"
#include "./1/bubble_sort.h"
#include "./1/insertion_sort.h"
#include "./1/selection_sort.h"
#include "./1/shell_sort.h"
#include "./2/heap_sort.h"
#include "./3/iterative_merge_sort.h"
#include "./3/recursive_merge_sort.h"
#include "./4/quick_sort.h"
#include "./4/one_branch_recursion.h"
#include "./4/lib_qsort.h"
#include "./8/LSD_sort.h"
#include "./8/MSD_sort.h"
#include "./5/pivot.h"
#include "./common.h"

int main ()
{
    run_tests ("./tests/big_tests/", (void*) heap_sort, "./Heap_6", 0, 1000000, 10000);

    return 0;
}