/*
移植来自RBTree的代码，实现的员工管理系统
红黑树具有良好的插入、删除和查找性能，适合用于动态数据集的管理。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "workerManager.h"

// 创建新节点
Node* createNode(int id, const char *name, int age, float salary) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->salary = salary;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->color = 1; // 新节点默认为红色
    return newNode;
}

// 左旋操作
void leftRotate(RedBlackTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋操作
void rightRotate(RedBlackTree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// 插入修复操作
void insertFixup(RedBlackTree *tree, Node *node) {
    Node *uncle;
    while (node->parent != NULL && node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(tree, node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(tree, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = 0;
}

// 插入节点
void insert(RedBlackTree *tree, int id, const char *name, int age, float salary) {
    Node *newNode = createNode(id, name, age, salary);
    Node *current = tree->root;
    Node *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (newNode->id < current->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == NULL) {
        tree->root = newNode;
    } else if (newNode->id < parent->id) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    insertFixup(tree, newNode);
}

// 查找节点
Node* search(RedBlackTree *tree, int id) {
    Node *current = tree->root;
    while (current != NULL && current->id != id) {
        if (id < current->id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

// 中序遍历（按ID排序输出）
void inorderTraversal(Node *node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("ID: %d, Name: %s, Age: %d, Salary: %.2f\n", node->id, node->name, node->age, node->salary);
        inorderTraversal(node->right);
    }
}

// 删除节点（简化版，仅删除叶子节点或只有一个子节点的节点）
void deleteNode(RedBlackTree *tree, Node *node) {
    if (node == NULL) return;

    // 如果是叶子节点或只有一个子节点
    Node *child;
    if (node->left != NULL && node->right != NULL) {
        printf("Deletion of nodes with two children is not implemented in this example.\n");
        return;
    }

    if (node->left != NULL) {
        child = node->left;
    } else {
        child = node->right;
    }

    if (child != NULL) {
        child->parent = node->parent;
    }

    if (node->parent == NULL) {
        tree->root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    free(node);
}

int main() {
    RedBlackTree tree = {NULL};

    // 插入员工信息
    insert(&tree, 101, "张三", 30, 5000.0);
    insert(&tree, 102, "李四", 28, 4500.0);
    insert(&tree, 103, "王五", 35, 6000.0);
    insert(&tree, 104, "赵六", 25, 4000.0);

    // 显示所有员工信息
    printf("所有员工信息：\n");
    inorderTraversal(tree.root);
    printf("\n");

    // 查找员工信息
    Node *employee = search(&tree, 102);
    if (employee != NULL) {
        printf("找到员工：ID=%d, Name=%s, Age=%d, Salary=%.2f\n", employee->id, employee->name, employee->age, employee->salary);
    } else {
        printf("未找到员工\n");
    }
    printf("\n");

    // 删除员工信息
    deleteNode(&tree, search(&tree, 103));
    printf("删除员工ID=103后的所有员工信息：\n");
    inorderTraversal(tree.root);
    printf("\n");

    return 0;
}