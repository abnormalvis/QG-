// 已知前序遍历和中序遍历的结果，求原本的二叉树
// 例如：
// 前序遍历：ABDECF
// 中序遍历：DBEACF
#include <stdio.h>
#include <stdlib.h>

// 前序遍历  根节点->左子树->右子树
// 中序遍历  左子树->根节点->右子树
typedef struct TreeNode
{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTreeNode(char data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *buildTree(char *preOrder, char *midOrder, int n)
{
    if (n <= 0)
    {
        return NULL;
    }
    TreeNode *root = createTreeNode(preOrder[0]);
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (midOrder[i] == preOrder[0]) // 找到根节点在中序遍历中的位置
        {
            // 递归构建左子树
            root->left = buildTree(preOrder + 1, midOrder, i);
            // 递归构建右子树
            root->right = buildTree(preOrder + i + 1, midOrder + i + 1, n - i - 1);
            break;
        }
    }
    return root;
}

// 层序遍历
void levelOrder(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    TreeNode *queue[100]; // 队列   用于存放结点指针
    int front = 0;
    int rear = 0;         // 队头和队尾
    queue[rear++] = root; // 根节点入队
    while (front < rear)  // 队列不为空时
    {
        TreeNode *node = queue[front++]; // 队头元素出队
        printf("%c ", node->data);       // 输出队头元素
        if (node->left != NULL)          // 如果左子树不为空
        {
            queue[rear++] = node->left; // 左子树入队
        }
        if (node->right != NULL) // 如果右子树不为空
        {
            queue[rear++] = node->right; // 右子树入队
        }
    }
    printf("\n");
    free(queue); // 释放队列
}

int main()
{
    char preOrder[] = "ABDECF";
    char midOrder[] = "DBEACF";
    printf("preOrder: %s\n", preOrder);
    printf("midOrder: %s\n", midOrder);
    printf("The orginal tree is :\n");
    TreeNode *root = buildTree(preOrder, midOrder, 6);
    levelOrder(root);
    return 0;
}