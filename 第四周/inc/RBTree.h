#ifndef __RBTREE_H__
#define __RBTREE_H__

typedef struct Node
{
    int key;             // 节点的键值
    int value;           // 节点的值
    struct Node *left;   // 左子节点
    struct Node *right;  // 右子节点
    struct Node *parent; // 父节点
    int color;           // 颜色（0表示黑色，1表示红色）
} Node;

typedef struct
{
    Node *root;
} RedBlackTree;

Node *createNode(int key, int value);
void leftRotate(RedBlackTree *tree, Node *x);
void rightRotate(RedBlackTree *tree, Node *y);
void insertFixup(RedBlackTree *tree, Node *node);
void insert(RedBlackTree *tree, int key, int value);
Node *search(RedBlackTree *tree, int key);
#endif