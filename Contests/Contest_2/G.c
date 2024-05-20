#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MOD     1000000000
#define COMMAND_LEN 10

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)

enum ERROR
{
    OK = 1,
    NONE = 0
};

typedef struct TreapNode TreapNode;

struct TreapNode
{
    int priority;
    int key;
    int subtree_size;
    
    TreapNode* parent;
    TreapNode* left;
    TreapNode* right;
};

typedef struct TreePair
{
    TreapNode* first;
    TreapNode* second;
}TreePair;

int get_size (TreapNode* node)
{
    return node ? node->subtree_size : 0;
}

void update (TreapNode* node)
{
    if (node == NULL)
        return;
    
    node->subtree_size = 1 + get_size (node->left) + get_size (node->right);
}

enum ERROR kstat (TreapNode* tree, int k, int* value)
{
    if (tree == NULL)
        return NONE;
    
    int temp = get_size (tree->left);

    if (k >= get_size(tree))
        return NONE;
    
    if (k < temp)
        kstat (tree->left, k, value);
    
    else
        if (k == temp)
        {
            *value = tree->key;
            return OK;
        }

        else
            kstat (tree->right, k - temp - 1, value);
}

enum ERROR next (TreapNode* tree, int value, int* next_value)
{
    TreapNode* curr_node = tree;
    bool control = 0;

    while (curr_node != NULL)
    {
        if (curr_node->key > value)
        {
            *next_value = curr_node->key;
            curr_node = curr_node->left;

            control = 1;
        }

        else
            curr_node = curr_node->right;
    }

    if (control == 0)
        return NONE;

    return OK;
}

enum ERROR prev (TreapNode* tree, int value, int* prev_value)
{
    TreapNode* curr_node = tree;
    bool control = 0;

    while (curr_node != NULL)
    {
        if (curr_node->key >= value)
            curr_node = curr_node->left;

        else
        {
            *prev_value = curr_node->key;
            curr_node = curr_node->right;

            control = 1;
        }
    }

    if (control == 0)
        return NONE;

    return OK;
}

int min (int a, int b)
{
    return (a > b) ? b : a;
}

int max (int a, int b)
{
    return (a > b) ? a : b;
}

TreapNode* construct_node (int new_value, int new_priority)
{
    TreapNode* new_node = (TreapNode*) calloc (1, sizeof (TreapNode));
    assert (new_node != NULL);

    new_node->key = new_value;
    new_node->priority = new_priority;
    new_node->subtree_size = 1;

    return new_node;
}

TreePair split (TreapNode* tree, int key)
{
    TreePair result = {};

    if (tree == NULL)
    {
        result.first = NULL;
        result.second = NULL;

        return result;
    }
    
    if (key < tree->key)
    {
        TreePair left_result = split (tree->left, key);
        
        tree->left = left_result.second;

        if (left_result.second != NULL)
            left_result.second->parent = tree;

        result.first = left_result.first;
        result.second = tree;

        update (left_result.first);
        update (left_result.second);
    }
    
    else
    {
        TreePair right_result = split (tree->right, key);

        tree->right = right_result.first;

        if (right_result.first != NULL)
            right_result.first->parent = tree;
        
        result.first = tree;
        result.second = right_result.second;

        update (right_result.first);
        update (right_result.second);
    }

    return result;
}

TreapNode* merge (TreapNode* t1, TreapNode* t2)
{
    if (t1 == NULL)
        return t2;

    if (t2 == NULL)
        return t1;

    if (t1->priority > t2->priority)
    {
        t2->left = merge (t1, t2->left);
        t2->left->parent = t2;
        update (t2);
        return t2;
    } 
    
    else
    {
        t1->right = merge (t1->right, t2);
        t1->right->parent = t1;
        update (t1);
        return t1;
    }
}

TreapNode* exists (TreapNode* tree, int searched_value)
{
    if (tree == NULL)
        return NULL;

    TreapNode* curr_node = tree;

    while (curr_node != NULL)
    {
        if (curr_node->key == searched_value)
            return curr_node;
        
        if (searched_value < curr_node->key)
            curr_node = curr_node->left;
        
        else
            curr_node = curr_node->right;
    }
    
    return NULL;
}

TreapNode* insert_number (TreapNode* tree, int new_value, int new_priority)
{
    TreapNode* new_node = construct_node (new_value, new_priority);
    assert (new_node != NULL);
    
    if (tree == NULL)
    {
        new_node->parent = NULL;
        return new_node;
    }

    if (exists (tree, new_value))
        return tree;
    
    TreePair pair = split (tree, new_value);

    update (pair.first);
    update (pair.second);
    
    tree = merge (pair.first, merge (new_node, pair.second));
    
    while (new_node != tree)
    {
        update (new_node);
        new_node = new_node->parent;
    }

    update (new_node);
    
    return new_node;
}

TreapNode* delete_number (TreapNode* tree, int deleted_value)
{
    TreapNode* deleted_node = exists (tree, deleted_value);

    if (deleted_node == NULL)
        return tree;

    TreapNode* node_parent = deleted_node->parent;
    TreapNode* new_subtree = merge (deleted_node->left, deleted_node->right);

    update (new_subtree);

    if (new_subtree != NULL)
        new_subtree->parent = node_parent;

    if (node_parent != NULL)
    {
        if (node_parent->key > deleted_node->key)
        node_parent->left = new_subtree;
    
        else
            if (node_parent->key < deleted_node->key)
                node_parent->right = new_subtree;
    }

    if (node_parent == NULL)
        return new_subtree;

    while (node_parent != tree)
    {
        update (node_parent);
        
        node_parent = node_parent->parent;
    }
    update (node_parent);

    return node_parent;
}

void delete_tree (TreapNode* node)
{
    if (node == NULL)
        return;
        
    delete_tree (node->left);
    delete_tree (node->right);

    free (node);
}

TreapNode* match_the_tree (TreapNode* tree, char* command, int curr_value, FILE* file_out)
{
    if (strcmp (command, "insert") == 0)
    {
        int curr_priority = rand () % MOD;
        tree = insert_number (tree, curr_value, curr_priority);

        return tree;
    }
        
    if (strcmp (command, "delete") == 0)
    {
        tree = delete_number (tree, curr_value);
            
        return tree;
    }
        
    if (strcmp (command, "exists") == 0)
    {
        if (exists (tree, curr_value))
            fprintf (file_out, "true\n");
            
        else
            fprintf (file_out, "false\n");

        return tree;
    }           
        
    if (strcmp (command, "next") == 0)
    {
        int searched_value = 0;
        if (next (tree, curr_value, &searched_value))
            fprintf (file_out, "%d\n", searched_value);
        
        else
            fprintf (file_out, "none\n");

        return tree;
    }

    if (strcmp (command, "prev") == 0)
    {
        int searched_value = 0;
        if (prev (tree, curr_value, &searched_value))
            fprintf (file_out, "%d\n", searched_value);
            
        else
            fprintf (file_out, "none\n");

        return tree;
    }
                                    
    if (strcmp (command, "kth") == 0)
    {
        int searched_value = 0;
        if (kstat (tree, curr_value, &searched_value))
            fprintf (file_out, "%d\n", searched_value);
            
        else
            fprintf (file_out, "none\n");

        return tree;
    }

    printf ("Seek mistake in scanning\n");
}

int main()
{
    FILE* file_in = fopen ("input.txt", "r");
    FILE* file_out = fopen ("output.txt", "w");
    assert ((file_in != NULL) && (file_out != NULL));

    int curr_value = 0;
    int curr_priority = 0;

    char* command = (char*) calloc (COMMAND_LEN, sizeof (char));
    assert (command != NULL);

    TreapNode* tree = NULL;

    while (fscanf (file_in, "%" STRLEN(COMMAND_LEN) "s\t%d\n", command, &curr_value) != EOF)
    {
        tree = match_the_tree (tree, command, curr_value, file_out);
    }

    delete_tree (tree);

    fclose (file_in);
    fclose (file_out);

    free (command);
    
    return 0;
}
