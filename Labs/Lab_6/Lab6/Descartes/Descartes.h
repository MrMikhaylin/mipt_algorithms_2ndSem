#ifndef _DESCARTES_H
#define _DESCARTES_H

#define MOD 1000000000

enum ERROR
{
    OK = 1,
    NONE = 0
};

typedef struct TreapNode TreapNode;

struct TreapNode
{
    int priority;
    int key;
    
    TreapNode* parent;
    TreapNode* left;
    TreapNode* right;
};

typedef struct TreePair
{
    TreapNode* first;
    TreapNode* second;
}TreePair;

TreapNode* insert_number (TreapNode* tree, int new_value, int new_priority);

TreapNode* delete_number (TreapNode* tree, int deleted_value);

TreapNode* merge (TreapNode* t1, TreapNode* t2);

TreePair split (TreapNode* tree, int key);

TreapNode* delete (TreapNode* tree, int* nums, size_t arr_length);

void delete_tree (TreapNode* node);


#endif