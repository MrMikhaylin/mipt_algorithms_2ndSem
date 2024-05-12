#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define NEW_CAP 10
#define MIN_LEN 10

typedef int elem_t;

enum ERROR
{
    OK = 1,
    FAULT = 0
};

struct stack
{
    void* data;
    size_t size;
    size_t capacity;
};

struct stack* stack_ctor (size_t elem_size, size_t new_capacity)
{
    struct stack* stk = (struct stack*) calloc (1, sizeof (struct stack));
    assert (stk != NULL);

    stk->capacity = new_capacity;
    stk->size = 0;
    
    stk->data = (void*) calloc (stk->capacity, elem_size);
    assert (stk->data != NULL);

    return stk;
}

enum ERROR stack_push (struct stack* stk, elem_t number)
{
    if (stk == NULL) return FAULT;

    if (stk->size == stk->capacity)
    {
        stk->data = (void*) realloc ((elem_t *)stk->data, 2 * stk->capacity * sizeof (elem_t));
        if (stk->data == NULL) return FAULT;
        
        stk->capacity *= 2;
    }

    ((elem_t*) (stk->data))[stk->size] = number;
    stk->size++;

    return OK;
}

enum ERROR stack_pop (struct stack* stk, elem_t* number)
{
    if ((stk == NULL) || (stk->size <= 0)) return FAULT;

    if (stk->size <= stk->capacity/4)
    {
        stk->data = (void*) realloc ((elem_t*) stk->data, stk->capacity * sizeof (elem_t)/2);
        if (stk->data == NULL) return FAULT;

        stk->capacity /= 2;
    }

    if (stk->size > 0)
    {
        *number = ((elem_t*) (stk->data))[stk->size - 1];
        ((elem_t*) (stk->data))[stk->size - 1] = 0;
        stk->size--;
    }

    else
        return FAULT;

    return OK;
}

enum ERROR stack_clear (struct stack* stk)
{
    if ((stk == NULL) || (stk->size < 0)) return FAULT;
    
    while (stk->size > 0)
    {
        ((elem_t*) (stk->data))[stk->size - 1] = 0;
        stk->size--;
    }

    return OK;
}

enum ERROR stack_back (struct stack* stk, elem_t* number)
{
    if ((stk == NULL) || (stk->size <= 0)) return FAULT;
    
    *number = ((elem_t*) (stk->data))[stk->size - 1];

    return OK;
}

bool match_command (struct stack* stk, char* command, FILE* file_out)
{
    int control_s = scanf ("%10s", command);
    assert (control_s);
    elem_t number = 0;

    if ((strcmp (command, "push")) == 0)
    {
        int control_d = scanf ("%d", &number);
        assert (control_d);

        stack_push (stk, number);
        fprintf (file_out, "ok\n");

        return true;
    }

    if ((strcmp (command, "pop")) == 0)
    {
        if (stack_pop (stk, &number))
            fprintf (file_out, "%d\n", number);
        
        else
            fprintf (file_out, "error\n");
        
        return true;
    }

    if ((strcmp (command, "back")) == 0)
    {
        if (stack_back (stk, &number))
            fprintf (file_out, "%d\n", number);
        
        else
            fprintf (file_out, "error\n");

        return true;
    }

    if ((strcmp (command, "size")) == 0)
    {
        fprintf (file_out, "%d\n", stk->size);
        
        return true;
    }

    if ((strcmp (command, "clear")) == 0)
    {
        stack_clear (stk); 
        fprintf (file_out, "ok\n");
        
        return true;
    }
                
    if ((strcmp (command, "exit")) == 0)
    {
        fprintf (file_out, "bye\n");
        
        return false;
    }
}

void stack_dtor (struct stack* stk)
{
    free (stk->data);
    free (stk);
}

int main()
{
    struct stack* stk = stack_ctor (sizeof (elem_t), NEW_CAP);

    char* command = (char*) calloc (MIN_LEN, sizeof (char));
    assert (command != NULL);

    FILE* file_out = fopen ("output.txt", "w");
    assert (file_out != NULL);

    while (1)
    {
        if (!match_command (stk, command, file_out))
            break;
    }

    stack_dtor (stk);
    free (command);

    fclose (file_out);
    
    return 0;
}