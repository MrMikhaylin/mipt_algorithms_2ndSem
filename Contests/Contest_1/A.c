#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef int elem_t; 

struct stack
{
    elem_t* data;
    size_t size;
    size_t capacity;
};

struct stack* st_ctor (size_t elem_size)
{
    struct stack* stk = (struct stack*) calloc (1, sizeof (struct stack));
    assert (stk != NULL);

    stk->capacity = 10000;
    stk->size = 0;
    
    stk->data = (elem_t*) calloc (stk->capacity, elem_size);
    assert (stk->data != NULL);

    return stk;
}

void st_push (struct stack* stk, elem_t number)
{
    assert (stk != NULL);

    if (stk->size == stk->capacity)
    {
        stk->data = (elem_t*) realloc ((elem_t *)stk->data, 2 * stk->capacity * sizeof (elem_t));
        stk->capacity *= 2;
    }

    stk->data[stk->size] = number;
    stk->size++;
}

void st_pop (struct stack* stk, elem_t* number)
{
    assert (stk != NULL);

    if (stk->size <= stk->capacity/4)
    {
        
        stk->data = (elem_t*) realloc ((elem_t*) stk->data, stk->capacity * sizeof (elem_t)/2);
        stk->capacity /= 2;
    }

    if (stk->size >= 0)
    {
        *number = stk->data[stk->size - 1];
        stk->size--;
    }

    else
        assert (false);
}

void st_clear (struct stack* stk)
{
    assert (stk != NULL);

    for (int i = stk->size - 1; i >= 0; i--)
        stk->data[i] = 0;
            
    stk->size = 0;
}

void st_back (struct stack* stk, elem_t* number)
{
    assert (stk != NULL);

    *number = stk->data[stk->size - 1];
}

int main()
{
    struct stack* stk = st_ctor (sizeof (elem_t));

    char* command = (char*) calloc (10, sizeof (char));
    assert (command != NULL);

    elem_t number = 0;

    FILE* dst = fopen ("output.txt", "w");
    assert (dst != NULL);

    while (1)
    {
        scanf ("%s", command);

        if (strcmp (command, "push") == 0)
        {
            scanf (" %d\n", &number);

            st_push (stk, number);
            fprintf (dst, "ok\n"); 
        }

        else
            if (strcmp (command, "pop") == 0)
                if (stk->size == 0)
                    fprintf (dst, "error\n");
                
                else
                {
                    st_pop (stk, &number);
                    fprintf (dst, "%d\n", number);
                }
                    

            else
                if (strcmp (command, "back") == 0)
                    if ((stk->size) == 0)
                        fprintf (dst, "error\n");
                    
                    else
                    {
                        st_back (stk, &number);
                        fprintf (dst, "%d\n", number);
                    }
                else
                    if (strcmp (command, "size") == 0)
                        fprintf (dst, "%d\n", stk->size);
        
                    else
                        if (strcmp (command, "clear") == 0)
                        {
                            st_clear (stk);
                            fprintf (dst, "ok\n");
                        }

                        else
                            if (strcmp (command, "exit") == 0)
                            {
                                fprintf (dst, "bye\n");
                                break;
                            }
    }

    free (command);
    free (stk);

    fclose (dst);
    
    return 0;
}