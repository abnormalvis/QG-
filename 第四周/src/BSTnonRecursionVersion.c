// 二叉排序树非递归版本，与递归版本的区别在于巧妙使用栈来保存节点
// 稍微挪用上一个BST的代码，但是在遍历的部分使用了一个栈来保存节点
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 构建二叉搜索树
typedef struct TreeNode
{
    int data;               // 节点值，这里就不使用泛型了，因为二叉搜索树一般也都是整数类型的
    struct TreeNode *left;  // 左子节点
    struct TreeNode *right; // 右子节点
    int flag;               // 标记，0表示未访问，1表示已访问
} *TreeNode;

typedef struct StackNode
{
    TreeNode data;          // 栈节点
    struct StackNode *next; // 指向下一个节点的指针
} *StackNode;

typedef struct TreeNode *Node;
// 栈
typedef Node T;                  // 这里栈内元素类型定义为上面的Node，也就是二叉树结点指针
typedef struct StackNode *SNode; // 这里就命名为SNode，不然跟上面冲突了就不好了

void initStack(SNode head)
{
    head->next = NULL;
}

_Bool pushStack(SNode head, T data)
{
    SNode node = malloc(sizeof(struct StackNode));
    if (node == NULL)
        return 0;
    node->next = head->next;
    node->data = data;
    head->next = node;
    return 1;
}

_Bool isEmpty(SNode head)
{
    return head->next == NULL;
}

T peekStack(SNode head)
{
    return isEmpty(head) ? NULL : head->next->data;
}

T popStack(SNode head)
{
    SNode top = head->next;
    head->next = head->next->next;
    T e = top->data;
    free(top);
    return e;
}

void preOrder(TreeNode root)
{
    struct StackNode stack; // 栈先搞出来
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // 两个条件，只有当栈空并且节点为NULL时才终止循环
        while (root)
        {                             // 按照我们的思路，先不断遍历左子树，直到没有为止
            pushStack(&stack, root);  // 途中每经过一个结点，就将结点丢进栈中
            printf("%d ", root->data); // 然后打印当前结点元素值
            root = root->left;        // 继续遍历下一个左孩子结点
        }
        root = popStack(&stack); // 经过前面的循环，明确左子树全部走完了，接着就是右子树了
        root = root->right;      // 得到右孩子，如果有右孩子，下一轮会重复上面的步骤；如果没有右孩子那么这里的root就被赋值为NULL了，下一轮开始会直接跳过上面的while，继续出栈下一个结点再找右子树
    }
}
void inOrder(Node root)
{
    struct StackNode stack;
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // 其他都不变
        while (root)
        {
            pushStack(&stack, root);
            root = root->left;
        }
        root = popStack(&stack);
        printf("%d ", root->data); // 只需要将打印时机延后到左子树遍历完成
        root = root->right;
    }
}

void postOrder(TreeNode root)
{
    struct StackNode stack;
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // 其他都不变
        while (root)
        {
            pushStack(&stack, root);
            root->flag = 0; // 首次入栈时，只能代表左子树遍历完成，所以flag置0
            root = root->left;
        }
        root = peekStack(&stack); // 注意这里只是获取到结点，并没有进行出栈操作，因为需要等待右子树遍历完才能出栈
        if (root->flag == 0)
        {                       // 如果仅仅遍历了左子树，那么flag就等于0
            root->flag = 1;     // 此时标记为1表示遍历右子树
            root = root->right; // 这里跟之前是一样的
        }
        else
        {
            printf("%d ", root->data); // 当flag为1时走这边，此时左右都遍历完成了，这时再打印值出来
            popStack(&stack);         // 这时再把对应的结点出栈，因为左右都完事了
            root = NULL;              // 置为NULL，下一轮直接跳过while，然后继续取栈中剩余的结点，重复上述操作
        }
    }
}
// 创建节点
TreeNode createTreeNode(int data)
{
    TreeNode node = malloc(sizeof(struct TreeNode));
    if (node == NULL)
    {
        // 分配内存失败，返回NULL
        return NULL;
    }
    node->data = data;
    node->left = NULL;  // 左子节点初始化为NULL
    node->right = NULL; // 右子节点初始化为NULL
    return node;
}

// 插入节点 递归实现
TreeNode insert(TreeNode root, int data)
{
    if (root)
    { // 如果树不为空
        if (root->data > data)
        { // 如果插入的值小于当前节点的值，则插入到左子树
            root->left = insert(root->left, data);
        }
        else
        { // 如果插入的值大于当前节点的值，则插入到右子树
            root->right = insert(root->right, data);
        }
    }
    else
    { // 如果树为空，则创建一个新的节点
        root = createTreeNode(data);
    }
    return root; // 返回根节点
}

TreeNode find(TreeNode root, int target)
{ // 查找节点 递归实现
    if (root == NULL)
    { // 如果树为空，则返回NULL
        return NULL;
    }
    if (root->data == target)
    { // 如果找到目标节点，则返回该节点
        return root;
    }
    if (root->data > target)
    { // 如果目标值小于当前节点的值，则在左子树中查找
        return find(root->left, target);
    }
    else
    { // 如果目标值大于当前节点的值，则在右子树中查找
        return find(root->right, target);
    }
}

TreeNode findMax(TreeNode root)
{ // 查找最大值节点 递归实现
    if (root == NULL)
    { // 如果树为空，则返回NULL
        return NULL;
    }
    while (root->right)
    { // 如果当前节点的右子节点不为空，则继续向右子树查找
        root = root->right;
    }
    return root; // 返回最大值节点
}

TreeNode deleteNode(TreeNode root, int target)
{
    if (!root)
        return NULL;
    if (root->data > target)
    {
        root->left = deleteNode(root->left, target);
    }
    else if (root->data < target)
    {
        root->right = deleteNode(root->right, target);
    }
    else
    {
        if (!root->left)
        {
            TreeNode temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right)
        {
            TreeNode temp = root->left;
            free(root);
            return temp;
        }
        TreeNode max = findMax(root->left);
        root->data = max->data;
        root->left = deleteNode(root->left, max->data);
    }
    return root;
}

int main()
{ // 测试代码
    TreeNode root = NULL;
    srand(time(NULL)); // 设置随机数种子
    for (int i = 0; i < 10; i++)
    {                              // 随机插入10个节点
        int data = rand() % 100;   // 生成随机值
        root = insert(root, data); // 插入节点
    }
    printf("前序遍历：\n");
    preOrder(root); // 前序遍历
    printf("\n");
    printf("中序遍历：\n");
    inOrder(root);
    printf("\n");
    printf("后序遍历：\n");
    postOrder(root); // 后序遍历
    printf("\n");
    int target = rand() % 100; // 随机生成一个目标值
    printf("查找目标值：%d\n", target);
    TreeNode targetNode = find(root, target); // 查找目标节点
    if (targetNode)
    { // 如果找到目标节点
        printf("找到目标节点：%d\n", targetNode->data);
    }
    else
    { // 如果没有找到目标节点
        printf("未找到目标节点：%d\n", target);
    }
    printf("删除目标值：%d\n", target);
    root = deleteNode(root, target); // 删除目标节点
    printf("删除后中序遍历：\n");
    inOrder(root); // 中序遍历
    printf("\n");
    return 0;
}