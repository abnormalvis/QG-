#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct ListNode_
{
    E element;
    struct ListNode_ *next;
} ListNode;                     // 移除多余的分号
typedef struct ListNode_ *Node; // 定义为指向结点的指针

// 初始化链表
void initList(Node head)
{
    head->next = NULL; // 头结点的next指向NULL
}

_Bool insertNode(Node head, E element, int index)
{
    // 判断是否能够插入
    if (index < 1)
        return 0;
    // 找到待插入节点的前一个节点
    while (--index)
    {
        head = head->next;
        if (head == NULL)
            return 0;
    }
    Node node = malloc(sizeof(struct ListNode_));
    if (node == NULL)
        return 0;
    node->element = element;
    node->next = head->next;
    head->next = node;
    return 1;
}

// 反转链表  双指针法
Node reverseList(Node head)
{
    Node prev = NULL; // 保存前一个节点
    Node curr = head->next; // 当前节点从头结点的下一个节点开始
    while (curr)      // 当前节点不为空
    {
        Node next = curr->next; // 保存下一个节点
        curr->next = prev;      // 当前节点指向前一个节点
        prev = curr;            // 前一个节点指向当前节点
        curr = next;            // 当前节点指向下一个节点
    }
    head->next = prev; // 更新头结点的next指向新的头节点
    return head;
}

// 打印链表
void printList(Node head)
{
    while(head->next != NULL)
    {
        printf("%d ", head->next->element);
        head = head->next;
    }
}

int main()
{
    Node head = malloc(sizeof(struct ListNode_));
    if (head == NULL)
    {
        printf("内存分配失败\n");
        return 1;
    }

    initList(head);
    insertNode(head, 1, 1);
    insertNode(head, 2, 2);
    insertNode(head, 3, 3);
    insertNode(head, 4, 4);
    printList(head);
    printf("\n");
    Node newhead = reverseList(head);
    printList(newhead);
    return 0;
}