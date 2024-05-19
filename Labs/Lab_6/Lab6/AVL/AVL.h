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

AVLNode* insert_number (AVLNode* tree, int key);

AVLNode* delete_number (AVLNode* tree, int value);

AVLNode* make_balance (AVLNode* node);

AVLNode* balancing (AVLNode* node, int key);

AVLNode* delete (AVLNode* tree, int* nums, size_t arr_length);

void delete_tree (AVLNode* node);


#endif