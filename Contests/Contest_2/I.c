#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define BUFF_SZE 4096
#define NEW_CAP  10

typedef struct SplayNode SplayNode;
typedef struct Stack Stack;

typedef SplayNode* elem_t;

enum ERROR
{
    OK = 1,
    FAULT = 0
};

struct Stack
{
    SplayNode** data;
    size_t size;
    size_t capacity;
};

struct SplayNode
{
    bool visited;
    char* key;
    char* connect;

    SplayNode* parent;
    SplayNode* left;
    SplayNode* right;
};

typedef struct TreePair
{
    SplayNode* first;
    SplayNode* second;
}TreePair;

Stack* stack_ctor (size_t elem_size, size_t new_capacity)
{
    Stack* stk = (Stack*) calloc (1, sizeof (Stack));
    assert (stk != NULL);

    stk->capacity = new_capacity;
    stk->size = 0;
    
    stk->data = (void*) calloc (stk->capacity, elem_size);
    assert (stk->data != NULL);

    return stk;
}

enum ERROR stack_push (Stack* stk, elem_t number)
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

elem_t stack_pop (Stack* stk)
{
    if ((stk == NULL) || (stk->size <= 0)) return FAULT;

    elem_t number = NULL;

    if (stk->size <= stk->capacity/4)
    {
        stk->data = (void*) realloc ((elem_t*) stk->data, stk->capacity * sizeof (elem_t)/2);
        if (stk->data == NULL) return FAULT;

        stk->capacity /= 2;
    }

    if (stk->size > 0)
    {
        number = ((elem_t*) (stk->data))[stk->size - 1];

        ((elem_t*) (stk->data))[stk->size - 1] = 0;

        stk->size--;
    }

    return number;
}


SplayNode* find_closest_lower (SplayNode* tree, char* key)
{
    SplayNode* closest = NULL;
    SplayNode* curr_node = tree;

    while (curr_node != NULL)
    {
        int compare = strcmp (key, curr_node->key);

        if (compare == 0)
            return curr_node;

        if (compare < 0)
            curr_node = curr_node->left;

        else
        {
            closest = curr_node;
            curr_node = curr_node->right;
        }
    }
    
    return closest;
}

TreePair split (SplayNode* tree)
{
    TreePair result = {};

    SplayNode* right_child = tree->right;
    if (right_child) right_child->parent = NULL;
    tree->right = NULL;

    result.first = tree;
    result.second = right_child;

    return result;
}

SplayNode* construct_node (char* key, char* connect)
{
    SplayNode* new_node = (SplayNode*) calloc (1, sizeof (SplayNode));
    assert (new_node != NULL);

    char* str_1 = strdup (key);
    char* str_2 = strdup (connect);
    
    new_node->connect = str_2;
    new_node->key = str_1;
    new_node->visited = 0;
    
    return new_node;
}

SplayNode* rotate_right (SplayNode* node1)
{
    SplayNode* node2 = node1->left;
    
    node1->left = node2->right;
    if (node2->right) node2->right->parent = node1;

    node2->right = node1;
    node2->parent = node1->parent;
    node1->parent = node2;
    
    if (node2->parent)
        if (strcmp (node2->parent->key, node2->key) > 0)
            node2->parent->left = node2;
        
        else
            node2->parent->right = node2;

    return node2;
}

SplayNode* rotate_left (SplayNode* node1)
{
    SplayNode* node2 = node1->right;

    node1->right = node2->left;
    if (node2->left) node2->left->parent = node1;

    node2->left = node1;
    node2->parent = node1->parent;
    node1->parent = node2;
    
    if (node2->parent)
        if (strcmp (node2->parent->key, node2->key) > 0)
            node2->parent->left = node2;
        
        else
            node2->parent->right = node2;

    return node2;
}

SplayNode* splay (SplayNode* node)
{
    while (node->parent)  // пока есть родитель (пока не пришли в вершину)
    {
        SplayNode* grand_parent = node->parent->parent;

        if (!grand_parent)   // нет деда (поворот zig)
        {
            if (node == node->parent->left)
                node = rotate_right (node->parent);
            
            else
                node = rotate_left (node->parent);

            return node;
        }
        //дед-отец-ребенок по одну сторону (поворот zig-zig)
        if (((node == node->parent->left) && (node->parent == grand_parent->left)) || 
        (((node == node->parent->right) && (node->parent == grand_parent->right))))
        {
            if ((node == node->parent->left) && (node->parent == grand_parent->left))
            {
                node = rotate_right (grand_parent);
                node = rotate_right (node);
            }
            
            else
            {
                node = rotate_left (grand_parent);
                node = rotate_left (node);
            }
        }
        // поворот zig-zag
        else
        {
            if ((node == node->parent->left) && (node->parent == grand_parent->right))
            {
                node = rotate_right (node->parent);
                node = rotate_left (node->parent);
            }

            else
            {
                node = rotate_left (node->parent);
                node = rotate_right (node->parent);
            }
        }
    }

    return node;
}

SplayNode* insert (SplayNode* tree, char* key, char* connect)
{
    SplayNode* new_node = construct_node (key, connect);

    if (tree == NULL)
        return new_node;

    SplayNode* closest = find_closest_lower (tree, key);

    if (closest == NULL)
    {
        new_node->right = tree; if (tree) tree->parent = new_node;
        return new_node;
    }

    tree = splay (closest);
    TreePair pair = split (tree);

    new_node->left = pair.first; if (pair.first) pair.first->parent = new_node;
    new_node->right = pair.second; if (pair.second) pair.second->parent = new_node;
    
    return new_node;
}

SplayNode* exists (SplayNode* tree, char* request)
{
    SplayNode* curr_node = tree;

    while (curr_node != NULL)
    {
        int compare = strcmp (request, curr_node->key);
        
        if (compare == 0)
            return curr_node;
        
        else
            if (compare < 0)
                curr_node = curr_node->left;
            
            else
                curr_node = curr_node->right;
    }

    return NULL;
}

char* search (SplayNode** pilot_tree, SplayNode** aircraft_tree, char* request)
{
    SplayNode* ask = exists (*pilot_tree, request);
    // search in the pilot_tree
    if (ask)
    {
        SplayNode* new_tree = splay (ask);
        *pilot_tree = new_tree;
        return new_tree->connect;
    }
        
    // search in the aircraft_tree
    else
    {
        ask = exists (*aircraft_tree, request);
        SplayNode* new_tree = splay (ask);
        *aircraft_tree = new_tree;
        return new_tree->connect;
    }
}

void delete_tree (SplayNode* tree)
{
    if (tree == NULL)
        return;

    Stack* stk = stack_ctor (sizeof (elem_t), NEW_CAP);
    assert (stk != NULL);

    SplayNode* curr_node = tree;
    
    stack_push (stk, curr_node);
    while (stk->size != 0)
    {
        SplayNode* curr_node = stack_pop (stk);
        assert (curr_node != NULL);

        SplayNode* ch_1 = curr_node->left;
        SplayNode* ch_2 = curr_node->right;

        curr_node->visited = 1;
        
        free (curr_node->key);
            free (curr_node->connect);
                free (curr_node);

        if (ch_1 != NULL)
            if (ch_1->visited == 0)
                stack_push (stk, ch_1);
        
        if (ch_2 != NULL)
            if (ch_2->visited == 0)
                stack_push (stk, ch_2);
    }
    
    free (stk->data);
    free (stk);
}

int main()
{
    FILE* file_in = fopen ("input.txt", "r");
    FILE* file_out = fopen ("output.txt", "w");
    assert ((file_in != NULL) && (file_out != NULL));

    int N = 0;
    fscanf (file_in, "%d\n", &N);

    SplayNode* pilot_tree = NULL;
    SplayNode* aircraft_tree = NULL;

    char pilot[BUFF_SZE] = {};
    char aircraft[BUFF_SZE] = {};

    for (int i = 0; i < N; i++)
    {
        fscanf (file_in, "%s %s\n", pilot, aircraft);
        
        pilot_tree = insert (pilot_tree, pilot, aircraft);
        aircraft_tree = insert (aircraft_tree, aircraft, pilot);
    }

    int Q = 0;
    fscanf (file_in, "%d\n", &Q);

    char* request = pilot;

    for (int i = 0; i < Q; i++)
    {
        fscanf (file_in, "%s\n", request);
        char* answer = search (&pilot_tree, &aircraft_tree, request);

        fprintf (file_out, "%s\n", answer);
    }

    delete_tree (pilot_tree);
    delete_tree (aircraft_tree);

    fclose (file_in);
    fclose (file_out);

    return 0;
}