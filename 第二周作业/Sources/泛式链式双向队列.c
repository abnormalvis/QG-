#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct DoublyLinkNode
{
    E val;
    struct DoublyLinkNode *next, *prev;
} DubblyLinkNode;

// 创建队列（头节点）
DubblyLinkNode *createQueue()
{
    DubblyLinkNode *head = (DubblyLinkNode *)malloc(sizeof(DubblyLinkNode));
    if (head == NULL)
    {
        printf("内存分配失败！");
        return NULL;
    }
    head->next = head;
    head->prev = head;
    return head;
}

// 头部插入
void push_front(DubblyLinkNode *head, int val)
{
    DubblyLinkNode *newNode = (DubblyLinkNode *)malloc(sizeof(DubblyLinkNode));
    newNode->val = val;
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
}

// 尾部插入
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

// 头部弹出
void pop_front(DubblyLinkNode *head)
{
    if (head->next == head)
    {
        printf("empty queue\n");
        return;
    }
    // 先获取要删除的节点   然后把要删除的节点的下一个节点的前一个节点指向头节点
    DubblyLinkNode *temp = head->next;
    printf("pop success, value: %d\n", temp->val); // 显示弹出的值
    head->next = temp->next;
    // 让要删除的节点的前一个节点指向头节点
    temp->next->prev = head;
    // 释放要删除的节点的内存
    free(temp);
    printf("弹出成功！");
}

// 尾部弹出
void pop_back(DubblyLinkNode *head)
{ // 参数名统一为 head
    if (head->prev == head)
    {
        printf("empty queue\n");
        return;
    }
    DubblyLinkNode *temp = head->prev;
    printf("pop success, value: %d\n", temp->val); // 显示弹出的值
    head->prev = temp->prev;
    temp->prev->next = head;
    free(temp);
    printf("弹出成功！");
}

// 打印队列
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
    printf("打印完毕！\n");
}

// 销毁队列
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
    printf("销毁完毕！\n");
}

int main()
{
    E data;
    DubblyLinkNode *queue = createQueue();
    if (!queue)
        printf("创建队列失败\n");
    return 0;
    printf("请输入操作：1、从头部入队，2、从尾部入队，3、从头部出队，4、从尾部出队，5、打印队列，6、退出\n");
    while (1)
    {
        int choice;
        if (scanf("%d", &choice) != 1)
        { // 检查输入是否合法
            printf("输入无效，请重新输入\n");
            while (getchar() != '\n'); // 清空缓冲区
            continue;
        }
        switch (choice)
        {
        case 1:
            printf("请输入数据：");
            if (scanf("%d", &data) != 1)
            {
                printf("输入不合法\n");
                while (getchar() != '\n');
                break;
            }
            push_front(queue, data);
            break;
        case 2:
            printf("请输入数据：");
            if (scanf("%d", &data) != 1)
            {
                printf("输入不合法\n");
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
            destroyQueue(queue); // 释放内存
            exit(0);
        default:
            printf("无效操作，请重新输入。\n");
        }
    }
    return 0;
}