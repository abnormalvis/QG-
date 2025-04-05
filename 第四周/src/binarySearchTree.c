#include <stdio.h>
#include <stdlib.h>

// 构建二叉搜索树
typedef struct TreeNode
{
    int val;            // 节点值，这里就不使用泛型了，因为二叉搜索树一般也都是整数类型的
    struct TreeNode *left;  // 左子节点
    struct TreeNode *right; // 右子节点
} *TreeNode;

struct Queue
    {
        TreeNode *data;
        int front;
        int rear;
        int size;
    };
// 创建节点
TreeNode * createTreeNode(int val)
{
    TreeNode node = malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        // 分配内存失败，返回NULL
        return NULL;
    }
    node->val = val;
    node->left = NULL;  // 左子节点初始化为NULL
    node->right = NULL; // 右子节点初始化为NULL
    return node;
}

// 插入节点 递归实现
TreeNode insert(TreeNode root, int val)
{
    if (root)
    {   // 如果树不为空
        if (root->val > val)
        {   // 如果插入的值小于当前节点的值，则插入到左子树
            root->left = insert(root->left, val);
        }
        else
        {   // 如果插入的值大于当前节点的值，则插入到右子树
            root->right = insert(root->right, val);
        }
    }
    else
    {   // 如果树为空，则创建一个新的节点
        root = createTreeNode(val);
    }
    return root;    // 返回根节点
}

void inOrder(TreeNode root)
{   // 中序遍历  左子树->根节点->右子树
    if (root == NULL)
    {   // 如果树为空，则返回
        return;
    }
    // 简单，无需多言
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

void preOrder(TreeNode root)
{   // 先序遍历  根节点->左子树->右子树
    if (root == NULL)
    {   // 如果树为空，则返回
        return;
    }
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(TreeNode root)
{   // 后序遍历  左子树->右子树->根节点
    if (root == NULL)
    {   // 如果树为空，则返回
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}
void bfs(TreeNode root)
{   // 层序遍历
    if (root == NULL)
    {   // 如果树为空，则返回
        return;
    }
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue->data = malloc(sizeof(TreeNode) * 100);
}
TreeNode find(TreeNode root, int target)
{   // 查找节点 递归实现
    if (root == NULL)
    {   // 如果树为空，则返回NULL
        return NULL;
    }
    if (root->val == target)
    {   // 如果找到目标节点，则返回该节点
        return root;
    }
    if (root->val > target)
    {   // 如果目标值小于当前节点的值，则在左子树中查找
        return find(root->left, target);
    }
    else
    {   // 如果目标值大于当前节点的值，则在右子树中查找
        return find(root->right, target);
    }
}

TreeNode findMax(TreeNode root)
{   // 查找最大值节点 递归实现
    if (root == NULL)
    {   // 如果树为空，则返回NULL
        return NULL;
    }
    while (root->right)
    {   // 如果当前节点的右子节点不为空，则继续向右子树查找
        root = root->right;
    }
    return root;    // 返回最大值节点
}

TreeNode deleteNode(TreeNode root, int target)
{   // 删除节点 递归实现
    if (root == NULL)
    {   // 如果树为空，则返回NULL
        return NULL;
    }
    else
    {
        // 找到目标节点
        if (root->val > target) 
        {   // 递归删除左子树
            root->left = deleteNode(root->left, target);
        }
        else if (root->val < target) 
        {   // 递归删除右子树
            root->right = deleteNode(root->right, target);
        }
        else
        {
            // 找到目标节点
            if (root->left != NULL || root->right == NULL) 
            {   // 左孩子不为空
                TreeNode max = findMax(root->left); // 找到左子树最大值
                root->val = max->val;               // 将左子树最大值替换到目标节点
                root->left = deleteNode(root->left, max->val);  // 删除左子树最大值节点 实际上是删除了目标节点
            }
            // 另一种情况是右孩子不为空，左孩子为空
            else if (root->left == NULL && root->right != NULL)
            {   // 右孩子不为空
                TreeNode temp = root;            // 保存当前节点
                root = root->right;              // 将右子树赋值给当前节点
                free(temp);
            }
            else
            {
                if (root->left && root->right)
                {                                                // 左右孩子都有的情况
                    TreeNode max = findMax(root->left);          // 寻找左子树中最大的元素(也可以是右子树中最小的元素)
                    root->val = max->val;                        // 找到后将值替换
                    root->left = deleteNode(root->left, root->val); // 替换好后，以同样的方式去删除那个替换上来的结点
                }
            }
            if (root->left == NULL && root->right == NULL && root->val == target)
            {
                // 左右孩子都为空 也就是叶子节点的情况
                free(root);
                return NULL;
            }
        }
    }
}

int main()
{   // 测试代码
    struct TreeNode *root = createTreeNode(5);
    insert(root, 3);
    insert(root, 8);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 9);
    inOrder(root);
    printf("\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    bfs(root);
    printf("\n");
    TreeNode *node = find(root, 4);
    deleteNode(root, 3);
    inOrder(root);
    printf("\n");
    return 0;
}