#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define BUFF_SZE 4096

typedef struct SplayNode SplayNode;

struct SplayNode
{
    char* key;
    char* connect;

    SplayNode* parent;
    SplayNode* left;
    SplayNode* right;
};

SplayNode* construct_node (char* key, char* connect)
{
    SplayNode* new_node = (SplayNode*) calloc (1, sizeof (SplayNode));
    assert (new_node != NULL);
    
    new_node->connect = connect;
    new_node->key = key;
    
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

    SplayNode* curr_node = tree;
    
    while (true)
    {
        if (curr_node->key == key)
            break;
    
        if (strcmp (key, curr_node->key) < 0)
            if (curr_node->left != NULL)
                curr_node = curr_node->left;
            
            else
            {
                new_node->parent = curr_node;
                curr_node->left = new_node;
                break;
            }
        
        else
            if (curr_node->right != NULL)
                curr_node = curr_node->right;
            
            else
            {
                new_node->parent = curr_node;
                curr_node->right = new_node;
                break;
            }
    }

    return splay (new_node);
}

SplayNode* find_note (SplayNode* tree, char* request)
{
    SplayNode* curr_node = tree;

    while (curr_node != NULL)
    {
        if (strcmp (curr_node->key, request) == 0)
            return curr_node;
        
        else
            if (strcmp (request, curr_node->key) < 0)
                curr_node = curr_node->left;
            
            else
                curr_node = curr_node->right;
    }

    return NULL;
}

char* search (SplayNode** pilot_tree, SplayNode** aircraft_tree, char* request)
{
    SplayNode* ask = find_note (*pilot_tree, request);
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
        ask = find_note (*aircraft_tree, request);
        SplayNode* new_tree = splay (ask);
        *aircraft_tree = new_tree;
        return new_tree->connect;
    }
}

void walk (SplayNode* node) 
{
    if (node == NULL)
        return;

    printf ("%s  connect:%s\n", node->key, node->connect);

    if (node->left != NULL)
        walk (node->left);
    
    if (node->right != NULL)
        walk (node->right);
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

    for (int i = 0; i < N; i++)
    {
        char* pilot = (char*) malloc (BUFF_SZE);
        char* aircraft = (char*) malloc (BUFF_SZE);
        assert (pilot && aircraft);

        fscanf (file_in, "%s %s\n", pilot, aircraft);
        
        pilot_tree = insert (pilot_tree, pilot, aircraft);
        aircraft_tree = insert (aircraft_tree, aircraft, pilot);
    }

    int Q = 0;
    fscanf (file_in, "%d\n", &Q);

    for (int i = 0; i < Q; i++)
    {
        char* request = (char*) malloc (BUFF_SZE);
        assert (request);

        fscanf (file_in, "%s\n", request);
        char* answer = search (&pilot_tree, &aircraft_tree, request);

        fprintf (file_out, "%s\n", answer);
    }

    fclose (file_in);
    fclose (file_out);

    return 0;
}