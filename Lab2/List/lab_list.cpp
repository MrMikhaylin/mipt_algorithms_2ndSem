#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ListStack_functions.h"
#include "../Tests/Tests.h"

int main ()
{
    struct ListStack* stack = stack_ctr ();
    
    double time_spent = 0.0;

    TEST_ONE(ListStack, &time_spent);
    
    printf ("list_test 1: %f\n", time_spent);

    TEST_TWO(ListStack, &time_spent);
    
    printf ("list_test 2: %f\n", time_spent);

    TEST_THREE(ListStack, &time_spent);
    
    printf ("list_test 3: %f\n", time_spent);

    stack_dtr (stack);

    printf ("After running test4, the results of the work on which the next schedule was built "
    "will be recorded in a file ListTest4.txt\n");

    TEST_FOUR(ListStack, "./ListTest4.txt");

    return 0;
}