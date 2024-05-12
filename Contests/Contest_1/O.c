#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DATA_MAX_SIZE 100000
#define MIN_LEN 15

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)

typedef struct Node Node;
typedef struct Heap Heap;

struct Node
{
    long value;
    size_t request;
};

struct Heap
{
    Node* data;
    size_t size;
};

Heap* HeapCtor ()
{
    Heap* heap = (Heap*) calloc (1, sizeof (Heap));
    assert (heap != NULL);

    heap->size = 0;
    heap->data = (Node*) calloc (DATA_MAX_SIZE, sizeof (Node));
    assert (heap->data != NULL);

    return heap;
}

void swap (Heap* heap, size_t parent, size_t index)
{
    assert (heap != NULL);

    long temporary_value = heap->data[parent].value;
    size_t temporary_request = heap->data[parent].request;

    heap->data[parent].request = heap->data[index].request;
    heap->data[parent].value = heap->data[index].value;
    
    heap->data[index].request = temporary_request;
    heap->data[index].value = temporary_value;
}

size_t get_parent (size_t index)
{
    return (index - 1)/2;
}

size_t get_left_child (size_t index)
{
    return 2 * index + 1;
}

size_t get_right_child (size_t index)
{
    return 2 * index + 2;
}

void sift_up (Heap* heap, size_t index)
{
    assert (heap != NULL);

    while (index > 0)
    {
        size_t parent = get_parent (index);

        if (heap->data[parent].value > heap->data[index].value)
        {
            swap (heap, parent, index);
            index = parent;
        }
    
        else
            return;
    }
}

void sift_down (Heap* heap, size_t index)
{
    assert (heap != NULL);

    int i_min = 0;

    while (index < heap->size)
    {
        i_min = index;
        size_t left_child = get_left_child (index);
        size_t right_child = get_right_child (index);
        
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

void insert (Heap* heap, long value, size_t request)
{
    assert (heap != NULL);

    heap->data[heap->size].value = value;
    heap->data[heap->size].request = request;
    heap->size++;
    
    sift_up (heap, heap->size - 1);
}

void getMin (Heap* heap, FILE* file)
{
    assert ((heap != NULL) && (file != NULL));

    fprintf (file, "%ld\n", heap->data[0].value);
}

void extractMin (Heap* heap)
{
    assert (heap != NULL);

    heap->data[0].value = heap->data[heap->size - 1].value;
    heap->data[0].request = heap->data[heap->size - 1].request;

    heap->data[heap->size - 1].value = 0;
    heap->data[heap->size - 1].request = 0;

    heap->size--;

    sift_down (heap, 0);
}

void decreaseKey (struct Heap* heap, int delta, size_t request)
{
    assert (heap != NULL);

    for (size_t i = 0; i < heap->size; i++)
    {
        if (heap->data[i].request == request)
        {
            heap->data[i].value -= delta;
            sift_up (heap, i);

            break;
        }
    }
}

void HeapDtor (Heap* heap)
{
    assert (heap != NULL);
    
    free (heap->data);
    free (heap);
}

void match_heap (Heap* heap, size_t num_of_request, char* command, FILE* dst)
{
    int number = 0;
    int delta = 0;

    for (size_t request = 1; request <= num_of_request; request++)
    {
        scanf ("%" STRLEN(MIN_LEN) "s", command);

        if (strcmp ("insert", command) == 0)
        {
            int contr = scanf ("%d", &number);
            assert (contr);

            insert (heap, number, request);

            continue;
        }
        
        if (strcmp ("getMin", command) == 0)
        {
            getMin (heap, dst);
            
            continue;
        }

        if (strcmp ("extractMin", command) == 0)
        {
            extractMin (heap);

            continue;
        }
                
        if (strcmp ("decreaseKey", command) == 0)
        {
            int contr = scanf ("%d %d", &number, &delta);
            assert (contr == 2);
            
            decreaseKey (heap, delta, number);

            continue;
        }

        else
            printf ("Seek mistake in scanning\n");
    }
}

int main()
{
    int q = 0;
    int control_q = scanf ("%d", &q);
    assert (control_q);

    char* command = (char*) calloc (MIN_LEN, sizeof (char));
    assert (command != NULL);
    
    FILE* dst = fopen ("output.txt", "w");
    assert ((dst != NULL) && (command != NULL));

    struct Heap* heap = HeapCtor ();
    match_heap (heap, q, command, dst);
    
    HeapDtor (heap);
    free (command);
    fclose (dst);

    return 0;
}