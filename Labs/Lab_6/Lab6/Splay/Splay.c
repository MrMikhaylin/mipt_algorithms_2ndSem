#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "Splay.h"

SplayNode* construct_node (int key)
{
    SplayNode* new_node = (SplayNode*) calloc (1, sizeof (SplayNode));
    assert (new_node != NULL);
    
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
        if (node2->parent->key > node2->key)
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
        if (node2->parent->key > node2->key)
            node2->parent->left = node2;
        
        else
            node2->parent->right = node2;

    return node2;
}

SplayNode* insert_number (SplayNode* tree, int key)
{
    SplayNode* new_node = construct_node (key);

    if (tree == NULL)
        return new_node;

    SplayNode* curr_node = tree;
    
    while (true)
    {
        if (curr_node->key == key)
            break;
    
        if (key < curr_node->key)
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

SplayNode* splay (SplayNode* node)
{
    while (node->parent)                                             // пока есть родитель (пока не пришли в вершину)
    {
        SplayNode* grand_parent = node->parent->parent;

        if (!grand_parent)                                           // нет деда (поворот zig)
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

SplayNode* delete (SplayNode* tree, int* nums, size_t arr_length)
{
    int index = rand() % arr_length;

    if (nums[index] != -1)
    {
        SplayNode* ans = delete_number (tree, nums[index]);
        nums[index] = -1;
        
        return ans;
    }

    else
        return delete (tree, nums, arr_length);
}

SplayNode* find_node (SplayNode* tree, int request)
{
    SplayNode* curr_node = tree;

    while (curr_node != NULL)
    {
        if (request == curr_node->key)
            return curr_node;
        
        else
            if (request < curr_node->key)
                curr_node = curr_node->left;
            
            else
                curr_node = curr_node->right;
    }

    return NULL;
}

SplayNode* merge (SplayNode* T1, SplayNode* T2)
{
    if (T1 == NULL)
        return T2;
    
    if (T2 == NULL)
        return T1;

    T1 = splay (find_max_node (T1));

    if (T1)
        T1->right = T2;
    
    if (T2)
        T2->parent = T1;
    
    return T1;
}

SplayNode* delete_number (SplayNode* tree, int key)
{
    SplayNode* curr_node = tree;
    SplayNode* deleted_node = find_node (tree, key);

    if (deleted_node == NULL)
        return tree;

    SplayNode* new_tree = splay (deleted_node);
    SplayNode* T1 = new_tree->left;
    SplayNode* T2 = new_tree->right;
    
    if (T1)
        T1->parent = NULL;
    if (T2)
        T2->parent = NULL;
    free (new_tree);

    SplayNode* ans = merge (T1, T2);

    return ans;
}

void delete_tree (SplayNode* node)
{
    if (node == NULL)
        return;
        
    delete_tree (node->left);
    delete_tree (node->right);

    free (node);
}

SplayNode* find_max_node (SplayNode* tree)
{
    if (tree == NULL)
        return NULL;

    SplayNode* max_node = tree;
    tree = tree->right;

    while (tree != NULL)
    {
        max_node = tree;
        tree = tree->right;
    }

    return max_node;
}