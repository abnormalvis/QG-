#include <stdio.h>
#include <stdlib.h>

// 后序遍历的顺序是：左子树->右子树->根节点 是一个递归的过程，和前序遍历类似，只是输出的顺序不同
typedef struct TreeNode         // 定义二叉树的结点结构
{
    int val;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

TreeNode * createTreeNode(int val)
{
    TreeNode * node = (TreeNode *)malloc(sizeof(TreeNode));
    if(node == NULL)
    {
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void postOrder(TreeNode * root)          // 从根节点开始遍历
{
    if(root == NULL)                    // 如果根节点为空，直接返回
    {
        return;
    }
    postOrder(root->left);               // 递归遍历左子树
    postOrder(root->right);              // 递归遍历右子树
    printf("%d\n", root->val);          // 输出根节点的值
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
    postOrder(root);
    return 0;
}