#ifndef _BST_H
#define _BST_H

typedef struct BSTNode BSTNode;

struct BSTNode
{
    int key;

    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* insert_number (BSTNode* tree, int key);

BSTNode* delete_number (BSTNode* tree, int value);

BSTNode* delete (BSTNode* tree, int* nums, size_t arr_length);

void delete_tree (BSTNode* node);


#endif