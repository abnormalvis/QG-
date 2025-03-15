#include <stdio.h>

typedef int E;
typedef struct ListNode_ {
    E element;
    struct ListNode_ *next;
} ListNode; // 移除多余的分号
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
    /*
    for(int i = 0; i < index - 1; ++i)
    {
        if(pre == NULL)
            return 0;
        pre = pre->next;
    }
    */
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

// 删除节点
_Bool deleteNode(Node head, int index)
{
    if (index < 1)
        return 0;
    while (--index)
    {
        head = head->next;
        if (head == NULL)
            printf("index out of range\n");
            return 0;
    }
    Node temp = head->next;
    head->next = temp->next;
    free(temp);
    return 1;
}


// 链表的翻转
void invertList(Node head) // 翻转链表
{  
    Node pre = NULL;
    Node cur = head->next;
    Node next = NULL;
    while(cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = pre;
}
E * getElement(Node head, int index)
{
    if(index < 1)
        return NULL;
    while(index--)
    {
        head = head->next;
        if(head == NULL)
            printf("index out of range\n");
            return NULL;
    }
    return &head->element;
}

int findElement(Node head, E element)
{
    while(head->next != NULL)
    {
        head = head->next;
        if(head->element == element)
            return &head->element;
    }
    return NULL;
}

int getLength(Node head)
{
    int length = 0;
    while(head->next != NULL)
    {
        head = head->next;
        length++;
    }
    return length;
}
void printList(Node head)
{
    while (head->next != NULL)
    {
        printf("%d ", head->next->element);
        //printf("打印完成\n");
        head = head->next;
    }
}
int main()
{
    // Node head = malloc(sizeof(struct ListNode_));   // 创建头结点
    // initList(head);
    struct ListNode_ head; // 创建头结点, 头结点本身就是Node
    initList(&head);       // initList函数接受一个指向Node的指针，这样它就可以修改原来的head指针，所以这里需要传入地址
    insertNode(&head, 1, 1);
    insertNode(&head, 2, 2);
    insertNode(&head, 3, 3);
    printList(&head);
    printf("\n");
    deleteNode(&head, 2);
    printList(&head);
    printf("\n");
    printf("%d\n", *getElement(&head, 2));
    findElement(&head, 2);
    return 0;
}
