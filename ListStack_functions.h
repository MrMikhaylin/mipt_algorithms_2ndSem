#ifndef LISTSTACK_FUNC_H_
#define LISTSTACK_FUNC_H_

typedef int elem_t;

const size_t MILLION = 1000000;

enum ERROR_CALL
{
    OK = 1,
    ERROR = 0
};

struct Node
{
    elem_t value;
    struct Node* next_node;
};

struct ListStack
{
    struct Node* list_head;
    size_t capacity;
};

struct ListStack* stack_ctr ();

struct ListStack* stack_dtr (struct ListStack* st);

ERROR_CALL push (struct ListStack* st, elem_t element);

elem_t top (struct ListStack* st);

ERROR_CALL pop (struct ListStack* st);


#endif