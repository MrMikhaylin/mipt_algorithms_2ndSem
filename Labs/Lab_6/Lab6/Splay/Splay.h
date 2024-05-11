#ifndef _SPLAY_H
#define _SPLAY_H

typedef struct SplayNode SplayNode;

struct SplayNode
{
    int key;

    SplayNode* parent;
    SplayNode* left;
    SplayNode* right;
};

SplayNode* construct_node (int key);

SplayNode* rotate_right (SplayNode* node1);

SplayNode* rotate_left (SplayNode* node1);

SplayNode* insert_number (SplayNode* tree, int key);

SplayNode* splay (SplayNode* node);

SplayNode* delete (SplayNode* tree, int* nums, size_t arr_length);

SplayNode* find_node (SplayNode* tree, int request);

SplayNode* merge (SplayNode* T1, SplayNode* T2);

SplayNode* delete_number (SplayNode* tree, int key);

SplayNode* find_max_node (SplayNode* tree);

void delete_tree (SplayNode* node);


#endif