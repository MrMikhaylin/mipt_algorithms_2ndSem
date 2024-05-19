#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "BST.h"

BSTNode* construct_node (int key);

BSTNode* get_top (BSTNode* node);

BSTNode* find_min (BSTNode* curr_node);

BSTNode* exists (BSTNode* tree, int value);



BSTNode* construct_node (int key)
{
    BSTNode* node = (BSTNode*) calloc (1, sizeof(BSTNode));
    assert (node != NULL);
    
    node->key = key;
    
    return (node);
}

BSTNode* insert_number (BSTNode* tree, int key)
{
    if (tree == NULL)
        return construct_node (key);

    if (key < tree->key)
    {
        tree->left = insert_number (tree->left, key);
        tree->left->parent = tree;
    }

    else
        if (key > tree->key)
        {
            tree->right = insert_number (tree->right, key);
            tree->right->parent = tree;
        }
        
        else
            return tree;

    return tree;
}

BSTNode* find_min (BSTNode* curr_node)
{
    if (curr_node == NULL)
        return NULL;

    while (curr_node->left != NULL)
        curr_node = curr_node->left;
    
    return curr_node;
}

BSTNode* delete_number (BSTNode* tree, int value)
{
    assert (tree != NULL);

    BSTNode* deleted_node = exists (tree, value);

    if (deleted_node == NULL)
        return tree;

    BSTNode* new = find_min (deleted_node->right);
    BSTNode* ans = NULL;

    if (new == NULL)                                                         // нет правого поддерева у удаляемого узла
    {
        if (deleted_node->parent == NULL)
            if (deleted_node->left == NULL)
            {
                free (deleted_node);
                
                return NULL;
            }

            else
            {
                ans = deleted_node->left;
                ans->parent = NULL;
                free (deleted_node);
            
                return ans;
            }

        if (deleted_node->left)
        {
            if (deleted_node->left->key < deleted_node->parent->key)
                deleted_node->parent->left = deleted_node->left;

            else
                deleted_node->parent->right = deleted_node->left;
               
            deleted_node->left->parent = deleted_node->parent;
        }
        
        else
            if (deleted_node->key < deleted_node->parent->key)
                deleted_node->parent->left = NULL;
            
            else
                deleted_node->parent->right = NULL;

        ans = deleted_node->parent;
        free (deleted_node);

        ans = get_top (ans);

        return ans;
    }
    
    if ((new->left == NULL) && (new->right == NULL))                         // new - лист
    {
        if (new->key < new->parent->key)
            new->parent->left = NULL;

        else
            new->parent->right = NULL;
    }

    else
    {
        new->right->parent = new->parent;
        
        if (new->right->key < new->parent->key)
            new->parent->left = new->right;
        
        else
            new->parent->right = new->right;
    }

    deleted_node->key = new->key;
    free (new);
    
    return get_top (deleted_node);
}

BSTNode* exists (BSTNode* tree, int value)
{
    BSTNode* curr_node = tree;

    while (curr_node != NULL)
    {
        if (curr_node->key == value)
            return curr_node;

        if (value < curr_node->key)
            curr_node = curr_node->left;
        
        else
            curr_node = curr_node->right;
    }

    return NULL;
}

BSTNode* get_top (BSTNode* node)
{
    if (node == NULL)
        return NULL;

    while (node->parent != NULL)
    {
        node = node->parent;
    }

    return node;
}

void delete_tree (BSTNode* node)
{
    if (node == NULL)
        return;

    delete_tree (node->left);
    delete_tree (node->right);

    free (node);
}

BSTNode* delete (BSTNode* tree, int* nums, size_t arr_length)
{
    int index = rand() % arr_length;

    if (nums[index] != -1)
    {
        BSTNode* ans = delete_number (tree, nums[index]);
        nums[index] = -1;
        
        return ans;
    }

    else
        return delete (tree, nums, arr_length);
}