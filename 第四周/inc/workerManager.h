#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

// 定义红黑树节点
typedef struct Node
{
    int id;              // 员工ID
    char name[50];       // 员工姓名
    int age;             // 员工年龄
    float salary;        // 员工薪资
    struct Node *left;   // 左子节点
    struct Node *right;  // 右子节点
    struct Node *parent; // 父节点
    int color;           // 颜色（0表示黑色，1表示红色）
} Node;

// 定义红黑树
typedef struct
{
    Node *root; // 树的根节点
} RedBlackTree;
// 创建新节点
Node *createNode(int id, const char *name, int age, float salary);
// 左旋操作
void leftRotate(RedBlackTree *tree, Node *x);
// 右旋操作
void rightRotate(RedBlackTree *tree, Node *y);
// 插入修复操作
void insertFixup(RedBlackTree *tree, Node *node);
// 插入节点
void insert(RedBlackTree *tree, int id, const char *name, int age, float salary);
// 查找节点
Node *search(RedBlackTree *tree, int id);
// 中序遍历（按ID排序输出）
void inorderTraversal(Node *node);
// 删除节点（简化版，仅删除叶子节点或只有一个子节点的节点）
void deleteNode(RedBlackTree *tree, Node *node);
#endif