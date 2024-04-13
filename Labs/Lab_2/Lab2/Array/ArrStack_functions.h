#ifndef ARRSTACK_FUNC_H_
#define ARRSTACK_FUNC_H_

#include <stddef.h>

typedef int elem_t;

#define MILLION 1000000

enum ERROR_CALL
{
    OK = 1,
    ERROR = 0
};

struct ArrStack
{
    void* data;
    size_t capacity;
    size_t size;
};

struct ArrStack* stack_ctr ();

struct ArrStack* stack_dtr (struct ArrStack* st);

enum ERROR_CALL push (struct ArrStack* st, elem_t element);

elem_t top (const struct ArrStack* st);

enum ERROR_CALL pop (struct ArrStack* st);


#endif