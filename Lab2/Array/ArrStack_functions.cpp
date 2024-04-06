#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"

struct ArrStack* stack_ctr ()
{
    struct ArrStack* new_stack = (struct ArrStack*) calloc (1, sizeof (struct ArrStack));
    assert (new_stack != nullptr);

    new_stack->capacity = 1;
    
    new_stack->data = (elem_t*) calloc (1, sizeof (elem_t));
    assert (new_stack->data != nullptr);
    
    new_stack->size = 0;

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
    assert (st->size <= st->capacity);
    
    if (st->size == st->capacity)
    {
        st->capacity = 2 * st->capacity;

        st->data = (elem_t*) realloc((elem_t*) st->data, st->capacity * sizeof(elem_t));
        assert (st->data != nullptr);
    }

    st->data[st->size] = element;
    st->size++;

    return OK;
}

elem_t top (struct ArrStack* st)
{
    assert (st != nullptr);

    return (st->data[st->size - 1]);
}

ERROR_CALL pop (struct ArrStack* st)
{
    assert (st != nullptr);

    if (st->size == 0)
        return ERROR;
    
    else
    {
        if (st->size <= st->capacity/4)
        {
            if (st->capacity >= 100)
            {
                st->data = (elem_t*) realloc ((elem_t*) st->data, st->capacity*sizeof(elem_t)/2);

                st->capacity = st->capacity/2;
            }
        }
        
        st->data[st->size - 1] = 0;
        st->size--;

        return OK;
    }
}