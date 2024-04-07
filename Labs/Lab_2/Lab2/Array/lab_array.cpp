#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"
#include "../Tests/Tests.h"

int main()
{
    struct ArrStack* stack = stack_ctr ();

    double time_spent = 0.0;

    TEST_ONE(ArrStack, &time_spent);

    printf ("array_test 1: %f\n", time_spent);
    
    TEST_TWO(ArrStack, &time_spent);
    
    printf ("array_test 2: %f\n", time_spent);

    TEST_THREE(ArrStack, &time_spent);
    
    printf ("array_test 3: %f\n", time_spent);

    stack_dtr (stack);

    printf ("After running test4, the results of the work on which the next schedule was built "
    "will be recorded in a file ArrayTest4.txt\n");

    TEST_FOUR(ArrStack, "./ArrayTest4.txt");

    return 0;
}
