#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int DATA_MAX_SIZE = 100000;

struct Node
{
    long value;
    int request;
};

struct Heap
{
    struct Node* data;
    int size;
};

struct Heap* HeapCtor ()
{
    struct Heap* heap = (struct Heap*) calloc (1, sizeof (struct Heap));
    assert (heap != NULL);

    heap->size = 0;
    heap->data = (struct Node*) calloc (DATA_MAX_SIZE, sizeof (struct Node));

    return heap;
}

void swap (struct Heap* heap, int parent, int index)
{
    assert (heap != NULL);

    long temporary_value = heap->data[parent].value;
    int temporary_request = heap->data[parent].request;

    heap->data[parent].request = heap->data[index].request;
    heap->data[parent].value = heap->data[index].value;
    
    heap->data[index].request = temporary_request;
    heap->data[index].value = temporary_value;
}

void sift_up (struct Heap* heap, int index)
{
    assert (heap != NULL);

    while (index > 0)
    {
        int parent = (index - 1)/2;

        if (heap->data[parent].value > heap->data[index].value)
        {
            swap (heap, parent, index);
            index = parent;
        }
    
        else
            return;
    }
}

void sift_down (struct Heap* heap, int index)
{
    assert (heap != NULL);

    int i_min = 0;

    while (index < heap->size)
    {
        i_min = index;
        int left_child = 2*index + 1;
        int right_child = 2*index + 2;
        
        if  ((left_child < heap->size) && (heap->data[left_child].value < heap->data[i_min].value))
            i_min = left_child;
    
        if ((right_child < heap->size) && (heap->data[right_child].value < heap->data[i_min].value))
            i_min = right_child;
        
        if (heap->data[index].value <= heap->data[i_min].value)
            break;

        swap (heap, index, i_min);
        index = i_min;
    }
}

void insert (struct Heap* heap, long value, int request)
{
    assert (heap != NULL);

    heap->data[heap->size].value = value;
    heap->data[heap->size].request = request;
    heap->size++;
    
    sift_up (heap, heap->size - 1);
}

void getMin (struct Heap* heap, FILE* file)
{
    assert ((heap != NULL) && (file != NULL));

    fprintf (file, "%ld\n", heap->data[0].value);
}

void extractMin (struct Heap* heap)
{
    assert (heap != NULL);

    heap->data[0].value = heap->data[heap->size - 1].value;
    heap->data[0].request = heap->data[heap->size - 1].request;

    heap->data[heap->size - 1].value = 0;
    heap->data[heap->size - 1].request = 0;

    heap->size--;

    sift_down (heap, 0);
}

void decreaseKey (struct Heap* heap, int delta, int request)
{
    assert (heap != NULL);

    for (int i = 0; i < heap->size; i++)
    {
        if (heap->data[i].request == request)
        {
            heap->data[i].value -= delta;
            sift_up (heap, i);

            break;
        }
    }
}

void HeapDtor (struct Heap* heap)
{
    assert (heap != NULL);
    
    free (heap->data);
    free (heap);
}

int main()
{
    int q = 0;
    scanf ("%d", &q);

    char* command = (char*) calloc (15, sizeof (char));
    FILE* dst = fopen ("output.txt", "w");
    assert ((dst != NULL) && (command != NULL));
    
    int number = 0;
    int delta = 0;

    struct Heap* heap = HeapCtor ();

    for (int request = 1; request <= q; request++)
    {
        scanf ("%s", command);

        if (strcmp ("insert", command) == 0)
        {
            scanf ("%d", &number);

            insert (heap, number, request);
        }

        else
        {
            if (strcmp ("getMin", command) == 0)
                getMin (heap, dst);
            
            else
            {
                if (strcmp ("extractMin", command) == 0)
                    extractMin (heap);
                
                else
                {
                    if (strcmp ("decreaseKey", command) == 0)
                    {
                        scanf ("%d %d", &number, &delta);
                        
                        decreaseKey (heap, delta, number);
                    }
                }
            }
        }
    }

    HeapDtor (heap);
    free (command);

    fclose (dst);

    return 0;
}