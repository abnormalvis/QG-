// �����������ǵݹ�汾����ݹ�汾��������������ʹ��ջ������ڵ�
// ��΢Ų����һ��BST�Ĵ��룬�����ڱ����Ĳ���ʹ����һ��ջ������ڵ�
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��������������
typedef struct TreeNode
{
    int data;               // �ڵ�ֵ������Ͳ�ʹ�÷����ˣ���Ϊ����������һ��Ҳ�����������͵�
    struct TreeNode *left;  // ���ӽڵ�
    struct TreeNode *right; // ���ӽڵ�
    int flag;               // ��ǣ�0��ʾδ���ʣ�1��ʾ�ѷ���
} *TreeNode;

typedef struct StackNode
{
    TreeNode data;          // ջ�ڵ�
    struct StackNode *next; // ָ����һ���ڵ��ָ��
} *StackNode;

typedef struct TreeNode *Node;
// ջ
typedef Node T;                  // ����ջ��Ԫ�����Ͷ���Ϊ�����Node��Ҳ���Ƕ��������ָ��
typedef struct StackNode *SNode; // ���������ΪSNode����Ȼ�������ͻ�˾Ͳ�����

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
    struct StackNode stack; // ջ�ȸ����
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // ����������ֻ�е�ջ�ղ��ҽڵ�ΪNULLʱ����ֹѭ��
        while (root)
        {                             // �������ǵ�˼·���Ȳ��ϱ�����������ֱ��û��Ϊֹ
            pushStack(&stack, root);  // ;��ÿ����һ����㣬�ͽ���㶪��ջ��
            printf("%d ", root->data); // Ȼ���ӡ��ǰ���Ԫ��ֵ
            root = root->left;        // ����������һ�����ӽ��
        }
        root = popStack(&stack); // ����ǰ���ѭ������ȷ������ȫ�������ˣ����ž�����������
        root = root->right;      // �õ��Һ��ӣ�������Һ��ӣ���һ�ֻ��ظ�����Ĳ��裻���û���Һ�����ô�����root�ͱ���ֵΪNULL�ˣ���һ�ֿ�ʼ��ֱ�����������while��������ջ��һ���������������
    }
}
void inOrder(Node root)
{
    struct StackNode stack;
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // ����������
        while (root)
        {
            pushStack(&stack, root);
            root = root->left;
        }
        root = popStack(&stack);
        printf("%d ", root->data); // ֻ��Ҫ����ӡʱ���Ӻ��������������
        root = root->right;
    }
}

void postOrder(TreeNode root)
{
    struct StackNode stack;
    initStack(&stack);
    while (root || !isEmpty(&stack))
    { // ����������
        while (root)
        {
            pushStack(&stack, root);
            root->flag = 0; // �״���ջʱ��ֻ�ܴ���������������ɣ�����flag��0
            root = root->left;
        }
        root = peekStack(&stack); // ע������ֻ�ǻ�ȡ����㣬��û�н��г�ջ��������Ϊ��Ҫ�ȴ���������������ܳ�ջ
        if (root->flag == 0)
        {                       // �����������������������ôflag�͵���0
            root->flag = 1;     // ��ʱ���Ϊ1��ʾ����������
            root = root->right; // �����֮ǰ��һ����
        }
        else
        {
            printf("%d ", root->data); // ��flagΪ1ʱ����ߣ���ʱ���Ҷ���������ˣ���ʱ�ٴ�ӡֵ����
            popStack(&stack);         // ��ʱ�ٰѶ�Ӧ�Ľ���ջ����Ϊ���Ҷ�������
            root = NULL;              // ��ΪNULL����һ��ֱ������while��Ȼ�����ȡջ��ʣ��Ľ�㣬�ظ���������
        }
    }
}
// �����ڵ�
TreeNode createTreeNode(int data)
{
    TreeNode node = malloc(sizeof(struct TreeNode));
    if (node == NULL)
    {
        // �����ڴ�ʧ�ܣ�����NULL
        return NULL;
    }
    node->data = data;
    node->left = NULL;  // ���ӽڵ��ʼ��ΪNULL
    node->right = NULL; // ���ӽڵ��ʼ��ΪNULL
    return node;
}

// ����ڵ� �ݹ�ʵ��
TreeNode insert(TreeNode root, int data)
{
    if (root)
    { // �������Ϊ��
        if (root->data > data)
        { // ��������ֵС�ڵ�ǰ�ڵ��ֵ������뵽������
            root->left = insert(root->left, data);
        }
        else
        { // ��������ֵ���ڵ�ǰ�ڵ��ֵ������뵽������
            root->right = insert(root->right, data);
        }
    }
    else
    { // �����Ϊ�գ��򴴽�һ���µĽڵ�
        root = createTreeNode(data);
    }
    return root; // ���ظ��ڵ�
}

TreeNode find(TreeNode root, int target)
{ // ���ҽڵ� �ݹ�ʵ��
    if (root == NULL)
    { // �����Ϊ�գ��򷵻�NULL
        return NULL;
    }
    if (root->data == target)
    { // ����ҵ�Ŀ��ڵ㣬�򷵻ظýڵ�
        return root;
    }
    if (root->data > target)
    { // ���Ŀ��ֵС�ڵ�ǰ�ڵ��ֵ�������������в���
        return find(root->left, target);
    }
    else
    { // ���Ŀ��ֵ���ڵ�ǰ�ڵ��ֵ�������������в���
        return find(root->right, target);
    }
}

TreeNode findMax(TreeNode root)
{ // �������ֵ�ڵ� �ݹ�ʵ��
    if (root == NULL)
    { // �����Ϊ�գ��򷵻�NULL
        return NULL;
    }
    while (root->right)
    { // �����ǰ�ڵ�����ӽڵ㲻Ϊ�գ������������������
        root = root->right;
    }
    return root; // �������ֵ�ڵ�
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
{ // ���Դ���
    TreeNode root = NULL;
    srand(time(NULL)); // �������������
    for (int i = 0; i < 10; i++)
    {                              // �������10���ڵ�
        int data = rand() % 100;   // �������ֵ
        root = insert(root, data); // ����ڵ�
    }
    printf("ǰ�������\n");
    preOrder(root); // ǰ�����
    printf("\n");
    printf("���������\n");
    inOrder(root);
    printf("\n");
    printf("���������\n");
    postOrder(root); // �������
    printf("\n");
    int target = rand() % 100; // �������һ��Ŀ��ֵ
    printf("����Ŀ��ֵ��%d\n", target);
    TreeNode targetNode = find(root, target); // ����Ŀ��ڵ�
    if (targetNode)
    { // ����ҵ�Ŀ��ڵ�
        printf("�ҵ�Ŀ��ڵ㣺%d\n", targetNode->data);
    }
    else
    { // ���û���ҵ�Ŀ��ڵ�
        printf("δ�ҵ�Ŀ��ڵ㣺%d\n", target);
    }
    printf("ɾ��Ŀ��ֵ��%d\n", target);
    root = deleteNode(root, target); // ɾ��Ŀ��ڵ�
    printf("ɾ�������������\n");
    inOrder(root); // �������
    printf("\n");
    return 0;
}