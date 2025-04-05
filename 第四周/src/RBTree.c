#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

Node *createNode(int key, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->color = 1; // 新节点默认为红色
    return newNode;
}

void leftRotate(RedBlackTree *tree, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        tree->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(RedBlackTree *tree, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL)
    {
        tree->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void insertFixup(RedBlackTree *tree, Node *node)
{
    while (node->parent != NULL && node->parent->color == 1)
    {
        if (node->parent == node->parent->parent->left)
        {
            Node *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == 1)
            {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    leftRotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(tree, node->parent->parent);
            }
        }
        else
        {
            Node *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == 1)
            {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rightRotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = 0; // 根节点始终为黑色
}

void insert(RedBlackTree *tree, int key, int value)
{
    Node *newNode = createNode(key, value);
    Node *current = tree->root;
    Node *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (newNode->key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == NULL)
    {
        tree->root = newNode;
    }
    else if (newNode->key < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    insertFixup(tree, newNode);
}

Node *search(RedBlackTree *tree, int key)
{
    Node *current = tree->root;
    while (current != NULL && current->key != key)
    {
        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

int main()
{
    RedBlackTree tree = {NULL};
    insert(&tree, 10, 100);
    insert(&tree, 20, 200);
    insert(&tree, 5, 50);

    Node *node = search(&tree, 20);
    if (node != NULL)
    {
        printf("Found: key=%d, value=%d\n", node->key, node->value);
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}