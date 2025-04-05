#include <stdio.h>
#include <stdlib.h>

typedef char E; // 定义元素类型为字符型

struct TreeNode
{
    E element;
    struct TreeNode *left;  // 左孩子
    struct TreeNode *right; // 右孩子
    int flag;               // 标记，0表示未访问，1表示已访问
};

typedef struct TreeNode *Node;
typedef Node T; // 将Node作为元素

struct QueueNode
{
    T element;              // 队列元素
    struct QueueNode *next; // 指向下一个节点的指针
};

typedef struct QueueNode *QNode;

struct Queue
{
    QNode front, rear;  // 队列的头指针和尾指针
};

typedef struct Queue *LinkedQueue;

_Bool initQueue(LinkedQueue queue)
{
    QNode node = malloc(sizeof(struct QueueNode));
    if (node == NULL)
        // 如果分配内存失败，返回0
        return 0;
    queue->front = queue->rear = node;  // 初始化队列的头指针和尾指针为同一个节点
    return 1;
}

_Bool offerQueue(LinkedQueue queue, T element)
{
    QNode node = malloc(sizeof(struct QueueNode));
    if (node == NULL)
        // 如果分配内存失败，返回0
        return 0;
    node->element = element;    // 将元素赋值给新节点
    queue->rear->next = node;   // 将新节点链接到队列的尾部
    queue->rear = node;         // 更新尾指针
    return 1;
}

_Bool isEmpty(LinkedQueue queue)
{
    // 判断队列是否为空，只需要判断空队列的头指针和尾指针是否相同
    return queue->front == queue->rear;
}

// 出队操作
T pollQueue(LinkedQueue queue)
{
    T e = queue->front->next->element;  // 获取队列头部元素 之所以返回的是next是因为front是一个哨兵节点
    // 哨兵节点的next指向第一个元素
    QNode node = queue->front->next;    // 保存头部节点
    queue->front->next = queue->front->next->next;  // 更新头指针
    if (queue->rear == node)
        // 如果队列只有一个元素，更新尾指针
        queue->rear = queue->front;     // 更新尾指针
    free(node);                         // 释放内存
    return e;                           // 返回出队元素
}

void levelOrder(Node root)
{
    struct Queue queue;       // 先搞一个队列
    initQueue(&queue);        // 初始化队列
    offerQueue(&queue, root); // 先把根节点入队
    while (!isEmpty(&queue))
    {                                  // 不断重复，直到队列空为止
        Node node = pollQueue(&queue); // 出队一个元素，打印值
        printf("%c", node->element);
        if (node->left)                     // 如果存在左右孩子的话
            offerQueue(&queue, node->left); // 记得将左右孩子入队，注意顺序，先左后右
        if (node->right)
            offerQueue(&queue, node->right);
    }
}

int main()
{
    // 创建一个简单的二叉树测试  
    // 可以自行修改节点的数据类型和结构，这里只做一个简单的测试
    Node root = malloc(sizeof(struct TreeNode));
    root->element = 'A';
    root->left = malloc(sizeof(struct TreeNode));
    root->left->element = 'B';
    root->left->left = malloc(sizeof(struct TreeNode));
    root->left->left->element = 'D';
    root->left->right = malloc(sizeof(struct TreeNode));
    root->left->right->element = 'E';

    levelOrder(root); // 层序遍历输出
    printf("\n");
}
