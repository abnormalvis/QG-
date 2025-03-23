// ջ����ʵ��
#include <stdio.h>
#include <stdlib.h>

// ����ջ�ڵ�ṹ
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

// ����һ���µ�ջ�ڵ�
StackNode *createNode(int data)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode)
    {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ���ջ�Ƿ�Ϊ��
int isEmpty(StackNode *root)
{
    return !root;
}

// ��ջ����
void push(StackNode **root, int data)
{
    if (data < 0)
    { // ʾ����У�����������Ƿ�Ϊ����
        printf("��Ч���ݣ�%d����ջʧ��\n", data);
        return;
    }
    StackNode *newNode = createNode(data);
    newNode->next = *root;
    *root = newNode;
    printf("%d ����ջ\n", data);
}

// ��ջ����
int pop(StackNode **root)
{
    if (isEmpty(*root))
    {
        printf("ջΪ�գ��޷���ջ\n");
        return -1;
    }
    StackNode *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    printf("%d �ѳ�ջ\n", popped);
    return popped;
}

// ��ȡջ��Ԫ��
int peek(StackNode *root)
{
    if (isEmpty(root))
    {
        printf("ջΪ�գ��޷���ȡջ��Ԫ��\n");
        return -1;
    }
    return root->data;
}

// ��ӡջ���ݣ���ջ����ջ�ף�
void printStack(StackNode *root)
{
    if (isEmpty(root))
    {
        printf("ջΪ��\n");
        return;
    }
    printf("��ǰջ���ݣ���ջ����ջ�ף���");
    StackNode *current = root;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ����������ջ����
int main()
{
    StackNode *root = NULL;
    int choice, value;
    int result; // ���ڼ��scanf�ķ���ֵ

    while (1)
    {
        printf("\n��ѡ�������\n");
        printf("1. ��ջ\n");
        printf("2. ��ջ\n");
        printf("3. �鿴ջ��Ԫ��\n");
        printf("4. ��ӡջ����\n");
        printf("5. �˳�\n");
        printf("������ѡ�");

        result = scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            printf("������Ҫ��ջ��ֵ��");
            result = scanf("%d", &value);
            if (result != 1)
            {
                while (getchar() != '\n'); // �����Ч����
                printf("��Ч���룬����������\n");
            }
            else
            {
                push(&root, value);
            }
            break;
        case 2:
            pop(&root);
            break;
        case 3:
            value = peek(root);
            if (value != -1)
            {
                printf("ջ��Ԫ���ǣ�%d\n", value);
            }
            break;
        case 4:
            printStack(root);
            break;
        case 5:
            printf("�������˳�\n");
            return 0;
        default:
            printf("��Чѡ�������ѡ��\n");
        }
    }

    return 0;
}