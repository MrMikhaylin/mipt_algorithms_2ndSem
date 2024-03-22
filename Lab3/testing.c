#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "testing.h"
#include "./1/Bubble_Sort.h"
#include "./1/Insertion_Sort.h"
#include "./1/Selection_Sort.h"
#include "./1/Shell_Sort.h"
#include "./2/Heap_Sort.h"
#include "./3/Iterative_Merge_Sort.h"
#include "./3/Recursive_Merge_Sort.h"
#include "./4/Quick_Sort.h"
#include "./4/OneBranch_Recursion.h"
#include "./4/Lib_QSort.h"
#include "./8/LSD_Sort.h"
#include "./8/MSD_Sort.h"
#include "./5/Pivot.h"
#include "./Common.h"

int main ()
{
    RunTests ("./tests/big_tests/", (void*) ItMerge_Sort, "./Merge", 0, 1000000, 10000);

    return 0;
}