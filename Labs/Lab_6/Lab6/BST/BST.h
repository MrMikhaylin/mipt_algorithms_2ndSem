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

BSTNode* construct_node (int key);

BSTNode* insert_number (BSTNode* tree, int key);

BSTNode* find_min (BSTNode* curr_node);

BSTNode* delete_number (BSTNode* tree, int value);

BSTNode* find_node (BSTNode* tree, int value);

BSTNode* get_top (BSTNode* node);

void delete_tree (BSTNode* node);


#endif