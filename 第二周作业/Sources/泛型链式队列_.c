#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct ListNode
{
    E data;
    struct ListNode *next;
} *Node;

typedef struct
{
    int queSize;
    Node front, rear;
} LinkedListQueue;

// 应对implicit declaration的报错 进行函数的声明
void dellinkedListQueue(LinkedListQueue *Queue);
void enQueue(LinkedListQueue *Queue, E data);      // 尾部入队
void enQueueFront(LinkedListQueue *Queue, E data); // 新增头部入队
E deQueue(LinkedListQueue *Queue);                 // 返回出队元素
void printQueue(LinkedListQueue *Queue);

// 创建队列（保持不变）
LinkedListQueue *createQueue()
{
    LinkedListQueue *q = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
    if (q == NULL)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    q->queSize = 0;
    q->front = q->rear = NULL; // 初始化为空
    return q;
}

// 销毁队列
void dellinkedListQueue(LinkedListQueue *Queue)
{
    if (Queue == NULL)
    {
        printf("队列指针为空，无法销毁\n");
        return;
    }
    while (Queue->front != NULL)
    {
        Node temp = Queue->front;
        Queue->front = Queue->front->next;
        free(temp);
    }
    free(Queue);
}

// 尾部入队
void enQueue(LinkedListQueue *Queue, E data)
{
    Node temp = (Node)malloc(sizeof(struct ListNode));
    temp->data = data;
    temp->next = NULL;
    if (Queue->rear == NULL)
    {
        Queue->front = Queue->rear = temp;
    }
    else
    {
        Queue->rear->next = temp;
        Queue->rear = temp;
    }
    Queue->queSize++;
}

// 新增头部入队函数
void enQueueFront(LinkedListQueue *Queue, E data)
{
    Node temp = (Node)malloc(sizeof(struct ListNode));
    temp->data = data;
    temp->next = Queue->front;
    Queue->front = temp;
    if (Queue->rear == NULL)
    { // 原队列为空
        Queue->rear = temp;
    }
    Queue->queSize++;
}

// 出队（原pop重命名，返回数据）
E deQueue(LinkedListQueue *Queue)
{
    if (Queue->front == NULL)
    {
        printf("Queue is empty!\n");
        return -1;
    }
    Node temp = Queue->front;
    E data = temp->data;
    Queue->front = Queue->front->next;
    if (Queue->front == NULL)
    {
        Queue->rear = NULL;
    }
    free(temp);
    Queue->queSize--;
    return data;
}

// 打印队列
void printQueue(LinkedListQueue *Queue)
{
    if (Queue->front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }
    Node current = Queue->front;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    E data;
    LinkedListQueue *queue = createQueue();
    if(queue == NULL)
        printf("Queue创建失败\n");
        return 0;
    printf("请输入操作：1、从头部入队 2、从尾部入队 3、从队头出队 4、打印队列 5、退出\n");
    while (1)
    {
        int choice;
        printf("请选择操作：");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
        {
            printf("无效的输入，请重新输入\n");
            continue;
        }
        switch (choice)
        {
        case 1: // 头部入队调用新函数
            enQueueFront(queue, data);
            break;
        case 2: // 尾部入队
            enQueue(queue, data);
            break;
        case 3: // 出队
            data = deQueue(queue);
            break;
        case 4:
            printQueue(queue);
            break;
        case 5:
            dellinkedListQueue(queue); // 修正函数名
            return 0;
        }
    }
    return 0;
}