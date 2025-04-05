// 中序遍历
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

//中序遍历  左子树->根节点->右子树
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

void midOrder(TreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    midOrder(root->left);
    printf("%d\n", root->val);
    midOrder(root->right);
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
    midOrder(root);
    return 0;
}