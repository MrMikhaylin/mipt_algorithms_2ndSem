#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"

struct ArrStack* stack_ctr (size_t size, size_t element_size)
{
    struct ArrStack* new_stack = (struct ArrStack*) calloc (1, sizeof (struct ArrStack));
    assert (new_stack != nullptr);

    new_stack->capacity = size;
    
    new_stack->data = (elem_t*) calloc (size, element_size);
    new_stack->fcp = 0;

    return new_stack;
}

struct ArrStack* stack_dtr (struct ArrStack* st)
{
    free (st->data);
    free (st);
    
    return nullptr;
}

ERROR_CALL push (struct ArrStack* st, elem_t element)
{
    assert (st != nullptr);
    assert (st->fcp <= st->capacity);
    
    if (st->fcp == st->capacity)
    {
        st->capacity = 2 * st->capacity;

        st->data = (elem_t*) realloc((elem_t*) st->data, st->capacity * sizeof(elem_t));
        assert (st->data != nullptr);
    }

    st->data[st->fcp] = element;
    st->fcp++;

    return OK;
}

elem_t top (struct ArrStack* st)
{
    assert (st != nullptr);

    return (st->data[st->fcp - 1]);
}

ERROR_CALL pop (struct ArrStack* st)
{
    assert (st != nullptr);

    if (st->fcp == 0)
        return ERROR;
    
    else
    {
        st->data[st->fcp - 1] = 0;
        st->fcp--;

        return OK;
    }
}