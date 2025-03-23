// 栈链的实现
#include <stdio.h>
#include <stdlib.h>

// 定义栈节点结构
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

// 创建一个新的栈节点
StackNode *createNode(int data)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 检查栈是否为空
int isEmpty(StackNode *root)
{
    return !root;
}

// 入栈操作
void push(StackNode **root, int data)
{
    if (data < 0)
    { // 示例：校验输入数据是否为负数
        printf("无效数据：%d，入栈失败\n", data);
        return;
    }
    StackNode *newNode = createNode(data);
    newNode->next = *root;
    *root = newNode;
    printf("%d 已入栈\n", data);
}

// 出栈操作
int pop(StackNode **root)
{
    if (isEmpty(*root))
    {
        printf("栈为空，无法出栈\n");
        return -1;
    }
    StackNode *temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    printf("%d 已出栈\n", popped);
    return popped;
}

// 获取栈顶元素
int peek(StackNode *root)
{
    if (isEmpty(root))
    {
        printf("栈为空，无法获取栈顶元素\n");
        return -1;
    }
    return root->data;
}

// 打印栈内容（从栈顶到栈底）
void printStack(StackNode *root)
{
    if (isEmpty(root))
    {
        printf("栈为空\n");
        return;
    }
    printf("当前栈内容（从栈顶到栈底）：");
    StackNode *current = root;
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 主函数测试栈操作
int main()
{
    StackNode *root = NULL;
    int choice, value;
    int result; // 用于检查scanf的返回值

    while (1)
    {
        printf("\n请选择操作：\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 查看栈顶元素\n");
        printf("4. 打印栈内容\n");
        printf("5. 退出\n");
        printf("请输入选项：");

        result = scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            printf("请输入要入栈的值：");
            result = scanf("%d", &value);
            if (result != 1)
            {
                while (getchar() != '\n'); // 清除无效输入
                printf("无效输入，请输入整数\n");
            }
            else
            {
                push(&root, value);
            }
            break;
        case 2:
            pop(&root);
            break;
        case 3:
            value = peek(root);
            if (value != -1)
            {
                printf("栈顶元素是：%d\n", value);
            }
            break;
        case 4:
            printStack(root);
            break;
        case 5:
            printf("程序已退出\n");
            return 0;
        default:
            printf("无效选项，请重新选择\n");
        }
    }

    return 0;
}