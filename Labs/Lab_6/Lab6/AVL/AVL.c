#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "AVL.h"

int height (AVLNode* node);

int max (int a, int b);

void update_height (AVLNode* node);

int get_balance (AVLNode* node);

AVLNode* construct_node (int key);

AVLNode* rotate_right (AVLNode* node1);

AVLNode* rotate_left (AVLNode* node1);

AVLNode* find_min (AVLNode* curr_node);

AVLNode* exists (AVLNode* tree, int value);



int height (AVLNode* node)
{
    if (node == NULL)
        return 0;
    
    return node->height;
}

void update_height (AVLNode* node)
{
    if (node == NULL)
        return;
    
    node->height = max (height (node->left), height (node->right)) + 1;
}

int max (int a, int b)
{
    return (a > b)? a : b;
}

AVLNode* construct_node (int key)
{
    AVLNode* node = (AVLNode*) calloc (1, sizeof(AVLNode));
    assert (node != NULL);
    
    node->key = key;
    node->height = 1;
    
    return (node);
}

AVLNode* rotate_right (AVLNode* node1)
{
    AVLNode* node2 = node1->left;
    
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

    node1->height = max (height (node1->left), height (node1->right)) + 1;
    node2->height = max (height (node2->left), height (node2->right)) + 1;

    return node2;
}

AVLNode* rotate_left (AVLNode* node1)
{
    AVLNode* node2 = node1->right;

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
    
    node1->height = max (height (node1->left), height (node1->right)) + 1;
    node2->height = max (height (node2->left), height (node2->right)) + 1;

    return node2;
}

int get_balance (AVLNode* node)
{
    if (node == NULL)
        return 0;

    return height (node->left) - height (node->right);
}

AVLNode* balancing (AVLNode* node, int key)
{
    if (node == NULL)
        return node;

    int balance = get_balance (node);
    node->height = max (height (node->left), height (node->right)) + 1;

    if ((balance > 1) && (key < node->left->key))
        return rotate_right (node);

    if ((balance < -1) && (key > node->right->key))
        return rotate_left (node);

    if ((balance > 1) && (key > node->left->key))
    {
        if (get_balance (node->left) < 0)
			node->left = rotate_left (node->left);
        
        return rotate_right (node);
    }

    if ((balance < -1) && (key < node->right->key))
    {
        if (get_balance (node->right) > 0)
		    node->right = rotate_right (node->right);
        
        return rotate_left (node);
    }

    return node;
}

AVLNode* insert_number (AVLNode* tree, int key)
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

    tree = balancing (tree, key);

    return tree;
}

AVLNode* find_min (AVLNode* curr_node)
{
    if (curr_node == NULL)
        return NULL;

    while (curr_node->left != NULL)
        curr_node = curr_node->left;
    
    return curr_node;
}

AVLNode* delete_number (AVLNode* tree, int value)
{
    assert (tree != NULL);

    AVLNode* deleted_node = exists (tree, value);
    
    if (deleted_node == NULL)
        return tree;
    
    AVLNode* new = find_min (deleted_node->right);
    AVLNode* ans = NULL;

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
        update_height (ans);
        free (deleted_node);

        return make_balance (ans);
    }
    
    if ((new->left == NULL) && (new->right == NULL))                         // new - лист
    {
        if (new->key < new->parent->key) new->parent->left = NULL;

        else new->parent->right = NULL;

        update_height (new->parent);
    }

    else
    {
        new->right->parent = new->parent;
        
        if (new->right->key < new->parent->key)
            new->parent->left = new->right;
        
        else
            new->parent->right = new->right;

        update_height (new->parent);
    }

    deleted_node->key = new->key;
    free (new);
    
    return make_balance (deleted_node);
}

AVLNode* exists (AVLNode* tree, int value)
{
    AVLNode* curr_node = tree;
    
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

AVLNode* make_balance (AVLNode* node)
{
    while (node->parent != NULL)
    {
        node = balancing (node, node->key);
        node = node->parent;
    }

    return balancing (node, node->key);
}

void delete_tree (AVLNode* node)
{
    if (node == NULL)
        return;

    delete_tree (node->left);
    delete_tree (node->right);

    free (node);
}

AVLNode* delete (AVLNode* tree, int* nums, size_t arr_length)
{
    int index = rand() % arr_length;

    if (nums[index] != -1)
    {
        AVLNode* ans = delete_number (tree, nums[index]);
        nums[index] = -1;
        
        return ans;
    }

    else
        return delete (tree, nums, arr_length);
}