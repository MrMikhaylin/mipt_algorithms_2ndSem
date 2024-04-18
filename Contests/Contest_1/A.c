#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct stack
{
    int data[10000];
    int size;
    int capacity;
};

struct stack* st_ctor ()
{
    struct stack* stk = (struct stack*) calloc (1, sizeof (struct stack));
    assert (stk != NULL);

    stk->capacity = 10000;
    stk->size = 0;

    return stk;
}

void st_push (struct stack* stk, int number, FILE* dst)
{
    assert ((stk != NULL) && (dst != NULL));

    stk->data[stk->size] = number;
    stk->size++;

    fprintf (dst, "ok\n"); 
}

void st_pop (struct stack* stk, FILE* dst)
{
    assert ((stk != NULL) && (dst != NULL));

    if ((stk->size) == 0)
        fprintf (dst, "error\n");
            
    else
    {
        int number = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        stk->size--;
                
        fprintf (dst, "%d\n", number);
    }
}

void st_clear (struct stack* stk, FILE* dst)
{
    assert ((stk != NULL) && (dst != NULL));

    for (int i = stk->size - 1; i >= 0; i--)
        stk->data[i] = 0;
            
    stk->size = 0;

    fprintf (dst, "ok\n");
}

void st_back (struct stack* stk, FILE* dst)
{
    assert ((stk != NULL) && (dst != NULL));

    if ((stk->size) == 0)
        fprintf (dst, "error\n");
            
    else
    {
        int number = stk->data[stk->size - 1];
                
        fprintf (dst, "%d\n", number);
    }
}

int main()
{
    struct stack* stk = st_ctor ();

    char* command = (char*) calloc (10, sizeof (char));
    assert (command != NULL);

    int number = 0;

    FILE* dst = fopen ("output.txt", "w");
    assert (dst != NULL);

    while (1)
    {
        scanf ("%s", command);

        if (strcmp (command, "push") == 0)
        {
            scanf (" %d\n", &number);

            st_push (stk, number, dst);
        }

        else
            if (strcmp (command, "pop") == 0)
                st_pop (stk, dst);

            else
                if (strcmp (command, "back") == 0)
                    st_back (stk, dst);

                else
                    if (strcmp (command, "size") == 0)
                        fprintf (dst, "%d\n", stk->size);
        
                    else
                        if (strcmp (command, "clear") == 0)
                            st_clear (stk, dst);

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