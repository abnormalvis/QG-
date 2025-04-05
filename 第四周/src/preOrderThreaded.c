#include <stdio.h>
#include <stdlib.h>

// 构建线索化二叉树
typedef struct TreeNode
{
    int val;
    struct TreeNode * left;
    struct TreeNode * right;
    int leftTag;
    int rightTag;
} TreeNode;

// 构建二叉树
TreeNode * createTreeNode(int val)
{
    TreeNode * node = malloc(sizeof(TreeNode));
    if(node == NULL)
    {
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->leftTag = 0;
    node->rightTag = 0;
    return node;
}

// 前序遍历
TreeNode * pre = NULL;
void preOrder(TreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    if(root->left == NULL)          // 如果左子树为空，把前一个节点的指针pre更新
    {
        root->left = pre;
        root->leftTag = 1;
    }
    if(root->right == NULL)
    {
        root->right = pre;
        root->rightTag = 1;
    }

    pre = root;
    if(root->leftTag == 0)
        preOrder(root->left);
    if(root->rightTag == 0)
        preOrder(root->right);
}

int main()
{
    TreeNode * root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);
    preOrder(root);
    return 0;
}