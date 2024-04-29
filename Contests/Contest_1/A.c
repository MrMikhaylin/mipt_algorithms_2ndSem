#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MIN_CAP 10
#define MIN_LEN 10

typedef int elem_t; 

struct stack
{
    void* data;
    size_t size;
    size_t capacity;
};

struct stack* stack_ctor (size_t elem_size)
{
    struct stack* stk = (struct stack*) calloc (1, sizeof (struct stack));
    assert (stk != NULL);

    stk->capacity = MIN_CAP;
    stk->size = 0;
    
    stk->data = (void*) calloc (stk->capacity, elem_size);
    assert (stk->data != NULL);

    return stk;
}

void stack_push (struct stack* stk, elem_t number)
{
    assert (stk != NULL);

    if (stk->size == stk->capacity)
    {
        stk->data = (void*) realloc ((elem_t *)stk->data, 2 * stk->capacity * sizeof (elem_t));
        assert (stk->data != NULL);

        stk->capacity *= 2;
    }

    ((elem_t*) (stk->data))[stk->size] = number;
    stk->size++;
}

void stack_pop (struct stack* stk, elem_t* number)
{
    assert (stk != NULL);

    if (stk->size <= stk->capacity/4)
    {
        
        stk->data = (void*) realloc ((elem_t*) stk->data, stk->capacity * sizeof (elem_t)/2);
        assert (stk->data != NULL);

        stk->capacity /= 2;
    }

    if (stk->size > 0)
    {
        *number = ((elem_t*) (stk->data))[stk->size - 1];
        ((elem_t*) (stk->data))[stk->size - 1] = 0;
        stk->size--;
    }

    else
        assert (false);
}

void stack_clear (struct stack* stk)
{
    assert (stk != NULL);
    assert (stk->size >= 0);
    
    while (stk->size > 0)
    {
        ((elem_t*) (stk->data))[stk->size - 1] = 0;
        stk->size--;
    }
}

void stack_back (struct stack* stk, elem_t* number)
{
    assert (stk != NULL);
    assert (stk->size > 0);

    *number = ((elem_t*) (stk->data))[stk->size - 1];
}

bool match_command (struct stack* stk, char* command, FILE* file_out)
{
    assert (scanf ("%s", command));
    elem_t number = 0;

    if ((strcmp (command, "push")) == 0)
    {
        assert (scanf ("%d", &number));

        stack_push (stk, number);
        fprintf (file_out, "ok\n");

        return true;
    }

    if ((strcmp (command, "pop")) == 0)
    {
        if (stk->size == 0)
            fprintf (file_out, "error\n");
                
        else
        {
            stack_pop (stk, &number);
            fprintf (file_out, "%d\n", number);
        }

        return true;
    }

    if ((strcmp (command, "back")) == 0)
    {
        if ((stk->size) == 0)
            fprintf (file_out, "error\n");
                    
        else
        {
            stack_back (stk, &number);
            fprintf (file_out, "%d\n", number);
        }

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

int main()
{
    struct stack* stk = stack_ctor (sizeof (elem_t));

    char* command = (char*) calloc (MIN_LEN, sizeof (char));
    assert (command != NULL);

    FILE* file_out = fopen ("output.txt", "w");
    assert (file_out != NULL);

    while (1)
    {
        if (!match_command (stk, command, file_out))
            break;
    }

    free (command);
    free (stk);

    fclose (file_out);
    
    return 0;
}