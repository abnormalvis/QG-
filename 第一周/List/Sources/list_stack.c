#include <stdio.h>
#include <stdlib.h>

// 基于链表实现的栈
typedef int E;

struct ListNode {
    E element;
    struct ListNode * next;
};

typedef struct ListNode * Node;

// 初始化栈
void initStack(Node head){
    head->next = NULL;
    head->element = -1;
}

int main(){
    struct ListNode head;
    initStack(&head);
    return 0;
}