#include <stdio.h>
#include <stdlib.h>

// 单链表的奇偶调换(例：1->2->3->4  变为 2->1->4->3)
typedef int E;
struct ListNode
{
    E element;
    struct ListNode * next;
};

typedef struct ListNode * Node;
// 初始化链表
void initList(Node * head)
{
    *head = (Node)malloc(sizeof(struct ListNode));
    if(*head == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    (*head)->next = NULL;
}
// 插入节点
void insertNode(Node head, E element, int index)
{
    // 判断是否能够插入
    if(index < 1)
    {
        printf("插入位置不合法\n");
        exit(1);
    }
    // 找到要插入的位置
    while(--index)
    {
        head = head->next;
        if (head == NULL)
            exit(1);
    }
    Node node = (Node)malloc(sizeof(struct ListNode));
    node->next = head->next;
    node->element = element;
    head->next = node;
}
// 交换奇偶节点
Node exchangeEvenOdd(Node dummy) {
    Node prev = dummy;        // 前驱指针初始指向哑节点
    Node current = dummy->next; // 当前指针指向第一个有效节点

    while (current && current->next) {
        // 记录三个关键节点
        Node first = current;
        Node second = current->next;
        Node nextPair = second->next;

        // 执行节点交换
        prev->next = second;  // 前驱连接新首节点
        second->next = first; // 新首节点连接旧首节点
        first->next = nextPair; // 旧首节点连接后续节点

        // 移动指针准备处理下一组
        prev = first;         // 前驱指针移动到交换后的后节点
        current = nextPair;   // 当前指针移动到下一组的首节点
    }
    return dummy; // 返回哑节点以保持链表完整性
}


// 打印链表
void printList(Node head)
{
    while(head->next != NULL)
    {
        printf("%d ", head->next->element);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    Node head;
    initList(&head);
    insertNode(head, 1, 1);
    insertNode(head, 2, 2);
    insertNode(head, 3, 3);
    insertNode(head, 4, 4);
    printList(head);
    printf("交换后：\n");
    Node newhead = exchangeEvenOdd(head);
    printList(newhead);
    // system("pause"); 可以视情况加上
    return 0;
}
