#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"

struct ArrStack* stack_ctr ()
{
    struct ArrStack* new_stack = (struct ArrStack*) calloc (1, sizeof (struct ArrStack));
    assert (new_stack != NULL);

    new_stack->capacity = 1;
    
    new_stack->data = (void*) calloc (1, sizeof (elem_t));
    assert (new_stack->data != NULL);
    
    new_stack->size = 0;

    return new_stack;
}

struct ArrStack* stack_dtr (struct ArrStack* st)
{
    assert (st != NULL);

    free (st->data);
    free (st);
    
    return NULL;
}

enum ERROR_CALL push (struct ArrStack* st, void* element)
{
    assert (st != NULL);
    assert (st->size <= st->capacity);
    
    if (st->size == st->capacity)
    {
        st->capacity = 2 * st->capacity;

        st->data = (void*) realloc((elem_t*) st->data, st->capacity * sizeof(elem_t));
        assert (st->data != NULL);
    }

    ((elem_t*) st->data)[st->size] = *((elem_t*) element);
    st->size++;

    return OK;
}

elem_t top (const struct ArrStack* st)
{
    assert (st != NULL);

    return (((elem_t*) st->data)[st->size - 1]);
}

enum ERROR_CALL pop (struct ArrStack* st)
{
    assert (st != NULL);

    if (st->size == 0)
        return ERROR;
    
    else
    {
        if (st->size <= st->capacity/4)
        {
            st->data = (void*) realloc ((elem_t*) st->data, st->capacity*sizeof(elem_t)/2);
            assert (st->data != NULL);

            st->capacity = st->capacity/2;
        }
        
        ((elem_t*) st->data)[st->size - 1] = 0;
        st->size--;

        return OK;
    }
}