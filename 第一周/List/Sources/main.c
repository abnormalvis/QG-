#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int global_size = 0; // 维护一个全局变量，用来记录链表的大小
bool is_list_initialized(int global_size);
// 链表交互系统
typedef int E;
typedef struct ListNode_
{
    E element;
    struct ListNode_ *next;
} *Node;

// 初始化链表
Node initList() // 不需要传递参数, 返回的结果是头结点
{
    printf("初始化链表中\n");
    Node head = (Node)malloc(sizeof(struct ListNode_)); // 为头结点分配内存
    if (head == NULL)
    {
        printf("内存分配失败, 初始化链表失败！\n");
        exit(1);
    }
    head->next = NULL; // 头结点的next指向NULL

    printf("请输出初始链表的大小：\n");
    int size;
    // 用一个数组存储用户初始化的链表元素
    int array[size];
    scanf("%d", &size);
    printf("请输入初始链表的元素：\n");
    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &array[i]);                             // 输入链表元素
        Node node = (Node)malloc(sizeof(struct ListNode_)); // 为新节点分配内存
        if (node == NULL)
        {
            printf("内存分配失败, 初始化链表失败！\n");
            global_size = 0; // 初始化失败，链表大小为0
            exit(1);
        }
        node->element = array[i]; // 赋值
        node->next = head->next;  // 新节点指向头结点的下一个节点
        head->next = node;        // 头结点指向新节点
        printf("第%d个元素插入成功\n", i + 1);
        global_size++;
    }
    return head;
}

// 插入元素
bool insertNode(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return false;
    }
    printf("准备插入新节点，請按顺序輸入要插入的元素和位置：\n");
    E element;
    int index;
    scanf("要插入的元素是%d 插入的位置是%d", &element, &index);
    // 判断是否能够插入
    if (index < 1)
    {
        printf("插入位置不合法\n");
        return false;
    }
    // 找到待插入节点的前一个节点
    while (--index)
    {
        head = head->next;
        if (head == NULL)
        {
            printf("插入位置不合法\n");
            return false;
        }
    }
    Node node = (Node)malloc(sizeof(struct ListNode_));
    if (node == NULL)
    {
        printf("内存分配失败, 插入失败！\n");
        exit(1);
    }
    node->element = element;
    node->next = head->next;
    head->next = node;
    global_size++;
    printf("插入成功\n");
    return true;
}

// 删除元素
bool deleteNode(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return false;
    }
    printf("准备删除节点，請按顺序輸入要删除的元素的位置：\n");
    int index;
    scanf("要删除的位置是%d", &index);
    // 判断是否能够删除
    if (index < 1)
    {
        printf("删除位置不合法\n");
        return false;
    }
    // 找到待删除节点的前一个节点
    while (--index)
    {
        head = head->next;
        if (head == NULL)
        {
            printf("删除位置不合法\n");
            return false;
        }
    }
    // 直接让待删除节点的前一个节点指向待删除节点的下一个节点
    Node node = head->next;
    if (node == NULL) // 待删除节点不存在，就直接把待删除节点的前一个节点指向NULL，然后释放待删除节点的内存
    {
        printf("删除位置不合法\n");
        return false;
    }
    head->next = node->next;
    free(node);
    global_size--;
    printf("删除成功\n");
    return true;
}

// 输出链表
void printList(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return;
    }
    printf("链表元素：\n");
    while (head->next != NULL)
    {
        printf("%d ->", head->next->element);
        head = head->next;
    }
    printf("链表打印完成!\n");
}

// 反转链表链表
Node reverseList(Node head)
{
    printf("准备反转链表\n");
    Node prev = NULL;       // 保存前一个节点
    Node curr = head->next; // 当前节点从头结点的下一个节点开始
    while (curr)            // 当前节点不为空
    {
        Node next = curr->next; // 保存下一个节点
        curr->next = prev;      // 当前节点指向前一个节点
        prev = curr;            // 前一个节点指向当前节点
        curr = next;            // 当前节点指向下一个节点
    }
    head->next = prev; // 更新头结点的next指向新的头节点
    printf("链表反转完成\n");
    return head;
}

// 判断成环
bool isCircle(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return false;
    }
    printf("准备判断链表是否成环\n"); // 快慢指针法
    Node slow = head->next;           // 慢指针
    Node fast = head->next;           // 快指针
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;       // 慢指针走一步
        fast = fast->next->next; // 快指针走两步
        if (slow == fast)        // 快慢指针相遇，说明链表成环
        {
            printf("链表成环\n");
            return true;
        }
    }
    printf("链表未成环\n");
    return false;
}

// 奇偶翻转
Node exchangeEvenOdd(Node dummy) // 创建一个虚拟头结点
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return NULL;
    }
    Node prev = dummy;          // 前驱指针初始指向虚拟头节点
    Node current = dummy->next; // 当前指针指向第一个有效节点

    while (current && current->next)
    {
        // 记录三个关键节点
        Node first = current;
        Node second = current->next;
        Node nextPair = second->next;

        // 执行节点交换
        prev->next = second;    // 前驱连接新首节点
        second->next = first;   // 新首节点连接旧首节点
        first->next = nextPair; // 旧首节点连接后续节点

        // 移动指针准备处理下一组
        prev = first;       // 前驱指针移动到交换后的后节点
        current = nextPair; // 当前指针移动到下一组的首节点
    }
    return dummy; // 返回哑节点以保持链表完整性
}

// 查询链表

void searchListIndex(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return;
    }
    printf("准备查询链表\n");
    printf("请输入要查询的下标：\n");
    int index;
    scanf("%d", &index);
    int i = 0;
    while (head->next != NULL)
    {
        if (i == index)
        {
            printf("下标为%d的元素是%d\n", index, head->next->element);
            return;
        }
        head = head->next;
        i++;
    }
    printf("待查询元素不在链表中\n");
}

// 查询中间节点
void searchMiddleNode(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return;
    }
    if (global_size / 2 == 0)
    {
        // 初始化快慢指针
        Node slow = head->next;
        Node fast = head->next->next;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        printf("中间节点是%d和%d\n", slow->element, slow->next->element);
    }
    else
    {
        Node slow = head->next;
        Node fast = head->next;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        printf("中间节点是%d\n", slow->element);
    }
    printf("查询中间节点完成\n");
}

// 构造循环链表
Node createCircleList(Node head)
{
    if (!is_list_initialized(global_size))
    {
        printf("请先初始化链表\n");
        return NULL;
    }
    printf("准备构造循环链表\n");
    Node tail = head;          // 尾节点
    while (tail->next != NULL) // 找到尾结点
    {
        tail = tail->next; // 移动尾结点
    }
    // 尾结点指向头结点
    tail->next = head->next;
    printf("构造循环链表完成\n");
    return head;
}

// 初始化菜单
void initMenu()
{
    printf("请输入需要的功能:\n");
    printf("1.初始化链表\n");
    printf("2.插入元素\n");
    printf("3.删除元素\n");
    printf("4.输出链表\n");
    printf("5.反转链表\n");
    printf("6.判断链表是否成环\n");
    printf("7.奇偶翻转\n");
    printf("8.查询链表\n");
    printf("9.查询中间节点\n");
    printf("10.构造循环链表\n");
    printf("11.退出\n");
}

// 判断用户是否需要先初始化链表
bool is_list_initialized(int global_size)
{
    // 检查链表大小是否合法
    if (global_size < 0)
    {
        fprintf(stderr, "链表大小非法: %d\n", global_size);
        return false;
    }

    // 检查链表是否已初始化
    if (global_size == 0)
    {
        fprintf(stderr, "请先初始化链表\n");
        return false;
    }

    return true;
}

int main()
{
    initMenu(); // 初始化菜单
    // 获取用户输入
    int choice;
    Node head = NULL;
    while (1)
    {
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            head = initList();
            break;
        case 2:
            insertNode(head);
            break;
        case 3:
            deleteNode(head);
            break;
        case 4:
            printList(head);
            break;
        case 5:
            head = reverseList(head);
            break;
        case 6:
            isCircle(head);
            break;
        case 7:
            exchangeEvenOdd(head);
            break;
        case 8:
            searchListIndex(head);
            break;
        case 9:
            searchMiddleNode(head);
            break;
        case 10:
            createCircleList(head);
            break;
        case 11:
            exit(0);
        default:
            printf("输入有误，请重新输入\n");
            break;
        }
    }
    return 0;
}