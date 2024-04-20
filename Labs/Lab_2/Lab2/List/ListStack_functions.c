#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ListStack_functions.h"

struct ListStack* stack_ctr ()
{
    struct ListStack* new_stack = (struct ListStack*) calloc (1, sizeof (struct ListStack));
    assert (new_stack != NULL);
    
    new_stack->list_head = NULL;

    return new_stack;
}

struct ListStack* stack_dtr (struct ListStack* st)
{
    assert (st != NULL);

    struct Node* temp = NULL;

    for (size_t i = 0; i < st->size; i++)
    {
        temp = st->list_head;

        st->list_head = st->list_head->next_node;
        st->size--;

        free (temp);
    }

    free (st);

    return NULL;
}

enum ERROR_CALL push (struct ListStack* st, void* element)
{
    assert (st != NULL);

    struct Node* new_node = (struct Node*) calloc (1, sizeof (struct Node));

    if (new_node == NULL)
        return ERROR;

    new_node->value = (elem_t*) element;
    new_node->next_node = st->list_head;
    
    st->size++;
    st->list_head = new_node;

    return OK;
}

elem_t top (const struct ListStack* st)
{
    assert (st != NULL);

    return *((elem_t*) st->list_head->value);
}

enum ERROR_CALL pop (struct ListStack* st)
{
    assert (st != NULL);

    if (st->size == 0) 
        return ERROR;

    struct Node* temp = st->list_head;

    st->list_head = st->list_head->next_node;
    st->size--;

    free (temp);
    
    return OK;    
}