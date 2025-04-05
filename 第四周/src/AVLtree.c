/*
ƽ����������ص�������������߶Ȳ����1��Ҫ������һ�㣬�����ɾ����������Ҫ������ת����������ƽ��
��ת������Ϊ���֣�������������˫��   ������LL�͡�RR�͡�LR�͡�RL��ʱ���ֱ��������������������+����������+����
�ڲ���ڵ�ʱ�����Ƚ�����ͨ�Ķ������������������Ȼ���ж��Ƿ���Ҫ������ת����������ƽ��
��ɾ���ڵ�ʱ�����Ƚ�����ͨ�Ķ���������ɾ��������Ȼ���ж��Ƿ���Ҫ������ת����������ƽ��
����ɾ���ڵ�ʱ�����ܻ���ֶ����������Ҫ���ж����ת����������ƽ��
����˵����ɾ���Ľڵ�ʱҶ�ӽڵ�ʱ��ֱ��ɾ��Ȼ�����ж��Ƿ���Ҫ������ת����������ƽ�⼴��
��ɾ���Ľڵ�ֻ��һ���ӽڵ�ʱ��ֱ�ӽ��ýڵ���ӽڵ��滻���ýڵ㣬Ȼ�����ж��Ƿ���Ҫ������ת����������ƽ�⼴��
��ɾ���Ľڵ��������ӽڵ�ʱ����Ҫ�ҵ��ýڵ������������С�ڵ㣬Ҳ����ֱ�Ӻ�̽ڵ㣬Ȼ�󽫸ýڵ��ֵ�滻���ýڵ��ֵ��Ȼ����ɾ���ýڵ������������С�ڵ㣬Ȼ�����ж��Ƿ���Ҫ������ת����������ƽ�⼴��

������ԣ�AVL���Ĳ����ɾ������ʹ���������ĸ߶Ⱦ����ܵر���ƽ�⣬�Ӷ�����˲���Ч��
*/
#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"
Node createNode(E element)
{
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    node->height = 1; // ��ʼ��ʱ���߶�дΪ1�Ϳ�����
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
{                                // ����������ʵ���Ͼ��ǰ���߽��������
    Node newRoot = root->right;  // �ȵõ���߽��
    root->right = newRoot->left; // ����߽�������������ԭ���������ұ�ȥ
    newRoot->left = root;        // �����µĸ������߾���ԭ���ĸ������

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
    { // ������ΪNULL��˵���ҵ��˲���λ�ã�ֱ�Ӵ����µľ�����
        root = createNode(element);
    }
    else if (root->element > element)
    { // �Ͷ���������һ�����жϴ�С�������ı����ıߣ�ֱ���ҵ���Ӧ����λ��
        root->left = insert(root->left, element);
        if (getHeight(root->left) - getHeight(root->right) > 1)
        {                                      // �������֮����Ҫ����ƽ�����ӣ������Ƿ�ʧ��
            if (root->left->element > element) // ������Ҫ�ж�һ���ǲ���������������߻����ұߣ����������Ǳ�˵����LL��������ұ���˵����LR
                root = rightRotation(root);    // LL�͵õ�����֮��Ľ�����õ��µĸ����
            else
                root = leftRightRotation(root); // LR�͵õ�������������֮��Ľ�����õ��µĸ����
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
    // ǰ��Ĳ������֮��ǵø���һ�����߶�
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return root; // ��󷵻�root����һ��
}

void inorderTraversal(Node root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left); // �ȱ���������
    printf("%d ", root->element);  // Ȼ����ʸ��ڵ�
    inorderTraversal(root->right); // ������������
}

void preorderTraversal(Node root)
{
    if (root == NULL)
        return;
    printf("%d ", root->element); // �ȷ��ʸ��ڵ�
    preorderTraversal(root->left); // Ȼ�����������
    preorderTraversal(root->right); // ������������
}
void postorderTraversal(Node root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left); // �ȱ���������
    postorderTraversal(root->right); // Ȼ�����������
    printf("%d ", root->element);     // �����ʸ��ڵ�
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
    printf("������������\n");
    inorderTraversal(root); // ����������
    printf("\n");
    printf("ǰ����������\n");
    preorderTraversal(root); // ǰ��������
    printf("\n");
    printf("������������\n");
    postorderTraversal(root); // ����������
    return 0;
}
