#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"
#include "ArrStack_tests.h"

int main()
{
    struct ArrStack* stack = stack_ctr (BASIC_ARRAY_SIZE, sizeof (elem_t));

    double time_spent = 0.0;

    time_spent = go_test_one (stack);

    printf ("array_test 1: %f\n", time_spent);
    
    time_spent = go_test_two (stack);
    
    printf ("array_test 2: %f\n", time_spent);

    time_spent = go_test_three (stack);
    
    printf ("array_test 3: %f\n", time_spent);

    stack_dtr (stack);

    printf ("After running test4, the results of the work on which the next schedule was built "
    "will be recorded in a file ArrayTest4.txt\n");

    test_four ();

    return 0;
}