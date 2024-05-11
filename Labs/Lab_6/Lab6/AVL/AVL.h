#ifndef _AVL_H
#define _AVL_H

typedef struct AVLNode AVLNode;

struct AVLNode
{
    int key;
    int height;

    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;
};

int height (AVLNode* node);

void update_height (AVLNode* node);

int max (int a, int b);

AVLNode* construct_node (int key);

AVLNode* rotate_right (AVLNode* node1);

AVLNode* rotate_left (AVLNode* node1);

int get_balance (AVLNode* node);

AVLNode* balancing (AVLNode* node, int key);

AVLNode* insert_number (AVLNode* tree, int key);

AVLNode* find_min (AVLNode* curr_node);

AVLNode* delete_number (AVLNode* tree, int value);

AVLNode* find_node (AVLNode* tree, int value);

AVLNode* make_balance (AVLNode* node);

void delete_tree (AVLNode* node);

AVLNode* delete (AVLNode* tree, int* nums, size_t arr_length);


#endif