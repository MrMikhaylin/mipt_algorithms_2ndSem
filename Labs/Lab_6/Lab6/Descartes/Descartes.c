#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "Descartes.h"

TreapNode* construct_node (int new_value, int new_priority)
{
    TreapNode* new_node = (TreapNode*) calloc (1, sizeof (TreapNode));
    assert (new_node != NULL);

    new_node->key = new_value;
    new_node->priority = new_priority;

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
    }
    
    else
    {
        TreePair right_result = split (tree->right, key);

        tree->right = right_result.first;

        if (right_result.first != NULL)
            right_result.first->parent = tree;
        
        result.first = tree;
        result.second = right_result.second;
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

        return t2;
    } 
    
    else
    {
        t1->right = merge (t1->right, t2);
        t1->right->parent = t1;

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
        return new_node;

    if (exists (tree, new_value))
        return tree;
    
    TreePair pair = split (tree, new_value);

    tree = merge (pair.first, merge (new_node, pair.second));
    
    while (new_node != tree)
    {
        new_node = new_node->parent;
    }
    
    return new_node;
}

TreapNode* delete_number (TreapNode* tree, int deleted_value)
{
    TreapNode* deleted_node = exists (tree, deleted_value);

    if (deleted_node == NULL)
        return tree;

    TreapNode* node_parent = deleted_node->parent;
    TreapNode* new_subtree = merge (deleted_node->left, deleted_node->right);

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
        node_parent = node_parent->parent;
    }

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

TreapNode* delete (TreapNode* tree, int* nums, size_t arr_length)
{
    int index = rand() % arr_length;

    if (nums[index] != -1)
    {
        TreapNode* ans = delete_number (tree, nums[index]);
        nums[index] = -1;
        
        return ans;
    }

    else
        return delete (tree, nums, arr_length);
}
