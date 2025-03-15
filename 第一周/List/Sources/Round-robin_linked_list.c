#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct _ListNode
{
	int data;
	struct _ListNode *next; // 指向结点的指针
}ListNode;// 定义链表结点：包含数据域，指针域

typedef ListNode* CyclicList;// 定义循环链表头指针，是指向结点的指针

// 初始化循环链表
CyclicList InitCyclicList(void)
{
    CyclicList L = (CyclicList)malloc(sizeof(ListNode));
    if(L == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    L->next = L;
    L->data = -1;
    return L;
}

// 插入结点
void insertNode(CyclicList L, E element, int index)
{
    if(index < 1)
    {
        printf("index out of range\n");
        return;
    }
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if(newNode == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = element;
    while(--index)
    {
        L = L->next;
        if(L == NULL)
        {
            printf("index out of range\n");
            return;
        }
    }
    newNode->next = L->next;
    L->next = newNode;
    L = newNode;
    printf("插入成功\n");
    return;
}

int main()
{
    CyclicList L = InitCyclicList();
    InsertCyclicList(L, 1, 1);
    return 0;
}