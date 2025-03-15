#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef struct Node
{
    E element;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node *node;

void initList(node head)
{
    head->next = NULL;
    head->prev = NULL;
}

_Bool insertNode(node head, E element, int index)
{
    // 判断是否能够插入
    if(index < 1)
        return 0;
    // 找到待插入节点的前一个节点
    while(--index)
    {
        head = head->next;
        if(head == NULL)
            return 0;
    }
    node newNode = malloc(sizeof(struct Node));
    if(newNode == NULL)
        return 0;
    newNode->element = element;
    if(head->next)
    {
        head->next->prev = newNode;
        newNode->next = head->next;
    }else{
        newNode->next = NULL; // 不存在直接将新节点后继指针指向NULL
    }
    head->next = newNode;
    newNode->prev = head;
    return 1;
}

_Bool deleteNode(node head, int index)
{
    // 判断是否能够删除
    if(index < 1)
        return 0;
    // 找到待删除节点的前一个节点
    while(--index)
    {
        head = head->next;
        if(head == NULL)
            return 0;
    }
    node temp = head->next;
    if(temp == NULL)
        return 0;
    head->next = temp->next;
    if(temp->next)
        temp->next->prev = head;
    free(temp);
    return 1;
}

E * getElement(node head, int index)
{
    // 判断是否能够获取
    if(index < 1)
        return NULL;
    // 找到待获取节点
    while(index--)
    {
        head = head->next;
        if(head == NULL)
            return NULL;
    }
    return &head->element;
}

int findElement(node head, E element)
{
    int index = 0;
    while(head->next)
    {
        head = head->next;
        index++;
        if(head->element == element)
            return index;
    }
    return -1;
}

void printList(node head)
{
    while(head->next)
    {
        head = head->next;
        printf("%d ->", head->element);
    }
    printf("\n");
}
int main()
{
    node head = NULL;
    initList(head);
    insertNode(head, 1, 1);
    insertNode(head, 2, 2);
    insertNode(head, 3, 3);
    findElement(head, 1);
    deleteNode(head, 1);
    printList(head);
    system("pause");
    return 0;
}


