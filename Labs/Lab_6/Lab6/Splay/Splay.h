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

SplayNode* insert_number (SplayNode* tree, int key);

SplayNode* delete_number (SplayNode* tree, int key);

SplayNode* merge (SplayNode* T1, SplayNode* T2);

SplayNode* splay (SplayNode* node);

SplayNode* delete (SplayNode* tree, int* nums, size_t arr_length);

void delete_tree (SplayNode* node);


#endif