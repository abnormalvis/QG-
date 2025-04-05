/*
平衡二叉树的特点就是左右子树高度差不超过1，要做到这一点，插入和删除操作都需要进行旋转操作来保持平衡
旋转操作分为三种：左旋、右旋、双旋   当出现LL型、RR型、LR型、RL型时，分别进行左旋、右旋、左旋+右旋、右旋+左旋
在插入节点时，首先进行普通的二叉搜索树插入操作，然后判断是否需要进行旋转操作来保持平衡
在删除节点时，首先进行普通的二叉搜索树删除操作，然后判断是否需要进行旋转操作来保持平衡
但是删除节点时，可能会出现多种情况，需要进行多次旋转操作来保持平衡
比如说，当删除的节点时叶子节点时，直接删除然后再判断是否需要进行旋转操作来保持平衡即可
当删除的节点只有一个子节点时，直接将该节点的子节点替换掉该节点，然后再判断是否需要进行旋转操作来保持平衡即可
当删除的节点有两个子节点时，需要找到该节点的右子树的最小节点，也就是直接后继节点，然后将该节点的值替换掉该节点的值，然后再删除该节点的右子树的最小节点，然后再判断是否需要进行旋转操作来保持平衡即可

总体而言，AVL树的插入和删除操作使得整棵树的高度尽可能地保持平衡，从而提高了查找效率
*/
#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"
Node createNode(E element)
{
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    node->height = 1; // 初始化时，高度写为1就可以了
    return node;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int getHeight(Node root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

Node leftRotation(Node root)
{                                // 左旋操作，实际上就是把左边结点拿上来
    Node newRoot = root->right;  // 先得到左边结点
    root->right = newRoot->left; // 将左边结点的左子树丢到原本根结点的右边去
    newRoot->left = root;        // 现在新的根结点左边就是原本的跟结点了

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    newRoot->height = max(getHeight(newRoot->right), getHeight(newRoot->left)) + 1;
    return newRoot;
}

Node rightRotation(Node root)
{
    Node newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    newRoot->height = max(getHeight(newRoot->right), getHeight(newRoot->left)) + 1;
    return newRoot;
}

Node leftRightRotation(Node root)
{
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

Node rightLeftRightRotation(Node root)
{
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

Node insert(Node root, E element)
{
    if (root == NULL)
    { // 如果结点为NULL，说明找到了插入位置，直接创建新的就完事
        root = createNode(element);
    }
    else if (root->element > element)
    { // 和二叉搜索树一样，判断大小，该走哪边走哪边，直到找到对应插入位置
        root->left = insert(root->left, element);
        if (getHeight(root->left) - getHeight(root->right) > 1)
        {                                      // 插入完成之后，需要计算平衡因子，看看是否失衡
            if (root->left->element > element) // 接着需要判断一下是插入了左子树的左边还是右边，如果是左边那边说明是LL，如果是右边那说明是LR
                root = rightRotation(root);    // LL型得到左旋之后的结果，得到新的根结点
            else
                root = leftRightRotation(root); // LR型得到先左旋再右旋之后的结果，得到新的根结点
        }
    }
    else if (root->element < element)
    {
        root->right = insert(root->right, element);
        if (getHeight(root->left) - getHeight(root->right) < -1)
        {
            if (root->right->element < element)
                root = leftRotation(root);
            else
                root = rightLeftRightRotation(root);
        }
    }
    // 前面的操作完成之后记得更新一下树高度
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return root; // 最后返回root到上一级
}

void inorderTraversal(Node root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left); // 先遍历左子树
    printf("%d ", root->element);  // 然后访问根节点
    inorderTraversal(root->right); // 最后遍历右子树
}

void preorderTraversal(Node root)
{
    if (root == NULL)
        return;
    printf("%d ", root->element); // 先访问根节点
    preorderTraversal(root->left); // 然后遍历左子树
    preorderTraversal(root->right); // 最后遍历右子树
}
void postorderTraversal(Node root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left); // 先遍历左子树
    postorderTraversal(root->right); // 然后遍历右子树
    printf("%d ", root->element);     // 最后访问根节点
}
int main()
{
    Node root = NULL;
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }
    printf("中序遍历结果：\n");
    inorderTraversal(root); // 中序遍历输出
    printf("\n");
    printf("前序遍历结果：\n");
    preorderTraversal(root); // 前序遍历输出
    printf("\n");
    printf("后序遍历结果：\n");
    postorderTraversal(root); // 后序遍历输出
    return 0;
}
