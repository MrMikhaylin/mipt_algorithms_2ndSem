#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ListStack_functions.h"

struct ListStack* stack_ctr ()
{
    struct ListStack* new_stack = (struct ListStack*) calloc (1, sizeof (struct ListStack));
    assert (new_stack != nullptr);
    
    new_stack->list_head = nullptr;

    return new_stack;
}

struct ListStack* stack_dtr (struct ListStack* st)
{
    assert (st != nullptr);

    struct Node* temp = nullptr;

    for (size_t i = 0; i < st->size; i++)
    {
        temp = st->list_head;

        st->list_head = st->list_head->next_node;
        st->size--;

        free (temp);
    }

    free (st);

    return nullptr;
}

ERROR_CALL push (struct ListStack* st, elem_t element)
{
    assert (st != nullptr);

    struct Node* new_node = (struct Node*) calloc (1, sizeof (struct Node));

    if (new_node == nullptr)
        return ERROR;

    new_node->value = element;
    new_node->next_node = st->list_head;
    
    st->size++;
    st->list_head = new_node;

    return OK;
}

elem_t top (struct ListStack* st)
{
    assert (st != nullptr);

    return st->list_head->value;
}

ERROR_CALL pop (struct ListStack* st)
{
    assert (st != nullptr);

    if (st->size == 0) 
        return ERROR;

    struct Node* temp = st->list_head;

    st->list_head = st->list_head->next_node;
    st->size--;

    free (temp);
    
    return OK;    
}