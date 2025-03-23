#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct DoublyLinkNode
{
    E val;
    struct DoublyLinkNode *next, *prev;
} DubblyLinkNode;

// �������У�ͷ�ڵ㣩
DubblyLinkNode *createQueue()
{
    DubblyLinkNode *head = (DubblyLinkNode *)malloc(sizeof(DubblyLinkNode));
    if (head == NULL)
    {
        printf("�ڴ����ʧ�ܣ�");
        return NULL;
    }
    head->next = head;
    head->prev = head;
    return head;
}

// ͷ������
void push_front(DubblyLinkNode *head, int val)
{
    DubblyLinkNode *newNode = (DubblyLinkNode *)malloc(sizeof(DubblyLinkNode));
    newNode->val = val;
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
}

// β������
void push_back(DubblyLinkNode *head, int val)
{
    DubblyLinkNode *newNode = (DubblyLinkNode *)malloc(sizeof(DubblyLinkNode));
    if (!newNode)
    {
        printf("malloc error\n");
        return;
    }
    newNode->val = val;
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
}

// ͷ������
void pop_front(DubblyLinkNode *head)
{
    if (head->next == head)
    {
        printf("empty queue\n");
        return;
    }
    // �Ȼ�ȡҪɾ���Ľڵ�   Ȼ���Ҫɾ���Ľڵ����һ���ڵ��ǰһ���ڵ�ָ��ͷ�ڵ�
    DubblyLinkNode *temp = head->next;
    printf("pop success, value: %d\n", temp->val); // ��ʾ������ֵ
    head->next = temp->next;
    // ��Ҫɾ���Ľڵ��ǰһ���ڵ�ָ��ͷ�ڵ�
    temp->next->prev = head;
    // �ͷ�Ҫɾ���Ľڵ���ڴ�
    free(temp);
    printf("�����ɹ���");
}

// β������
void pop_back(DubblyLinkNode *head)
{ // ������ͳһΪ head
    if (head->prev == head)
    {
        printf("empty queue\n");
        return;
    }
    DubblyLinkNode *temp = head->prev;
    printf("pop success, value: %d\n", temp->val); // ��ʾ������ֵ
    head->prev = temp->prev;
    temp->prev->next = head;
    free(temp);
    printf("�����ɹ���");
}

// ��ӡ����
void print_queue(DubblyLinkNode *head)
{
    if (head->next == head)
    {
        printf("Queue is empty\n");
        return;
    }
    DubblyLinkNode *temp = head->next;
    while (temp != head)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("��ӡ��ϣ�\n");
}

// ���ٶ���
void destroyQueue(DubblyLinkNode *head)
{
    if (!head)
        return;
    DubblyLinkNode *current = head->next;
    while (current != head)
    {
        DubblyLinkNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(head);
    printf("������ϣ�\n");
}

int main()
{
    E data;
    DubblyLinkNode *queue = createQueue();
    if (!queue)
        printf("��������ʧ��\n");
    return 0;
    printf("�����������1����ͷ����ӣ�2����β����ӣ�3����ͷ�����ӣ�4����β�����ӣ�5����ӡ���У�6���˳�\n");
    while (1)
    {
        int choice;
        if (scanf("%d", &choice) != 1)
        { // ��������Ƿ�Ϸ�
            printf("������Ч������������\n");
            while (getchar() != '\n'); // ��ջ�����
            continue;
        }
        switch (choice)
        {
        case 1:
            printf("���������ݣ�");
            if (scanf("%d", &data) != 1)
            {
                printf("���벻�Ϸ�\n");
                while (getchar() != '\n');
                break;
            }
            push_front(queue, data);
            break;
        case 2:
            printf("���������ݣ�");
            if (scanf("%d", &data) != 1)
            {
                printf("���벻�Ϸ�\n");
                while (getchar() != '\n');
                break;
            }
            push_back(queue, data);
            break;
        case 3:
            pop_front(queue);
            break;
        case 4:
            pop_back(queue);
            break;
        case 5:
            print_queue(queue);
            break;
        case 6:
            destroyQueue(queue); // �ͷ��ڴ�
            exit(0);
        default:
            printf("��Ч���������������롣\n");
        }
    }
    return 0;
}