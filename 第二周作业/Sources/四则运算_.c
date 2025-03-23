#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX 100 // 栈最大长度
/*
符号 括号 优先其次  再其次 +-
中->前 符号放前面
中->后 符号放后面
前->中 从右向左扫描操作数 从左向右出栈
后->中 从左向右扫描操作数 从右向左出栈
*/

// 用一个字符串数组来存贮输入的中缀表达式 然后把中缀表达式转换为前缀表达式，接着把前缀表达式从右向左扫描，从左向右出栈

#define STACK_EMPTY (-1)

// 辅助函数：检查字符是否为合法运算符或括号
int is_valid_char(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}' ||
           c == '[' || c == ']' || c == '+' || c == '-' ||
           c == '*' || c == '/' || c == ' ' || isdigit(c);
}

// 辅助函数：检查括号是否匹配
int is_matching_pair(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

// 检测中缀表达式是否合法
int check_infix_expression(char *infix_expression)
{
    if (infix_expression == NULL || infix_expression[0] == '\0')
    {
        return 0; // 处理空指针或空字符串
    }

    size_t len = strlen(infix_expression);
    if (len == 0)
    {
        return 1; // 空字符串视为合法
    }

    // 动态分配栈，大小为字符串长度
    int *stack = (int *)malloc(len * sizeof(int));
    if (stack == NULL)
    {
        return 0; // 内存分配失败
    }

    int top = STACK_EMPTY; // 栈顶指针初始化

    for (size_t i = 0; i < len; i++)
    {
        char c = infix_expression[i];

        // 检查字符合法性
        if (!is_valid_char(c))
        {
            free(stack);
            return 0; // 非法字符
        }

        // 处理左括号，压入栈
        if (c == '(' || c == '{' || c == '[')
        {
            stack[++top] = c;
        }
        // 处理右括号，弹出栈并检查匹配
        else if (c == ')' || c == '}' || c == ']')
        {
            if (top == STACK_EMPTY || !is_matching_pair(stack[top], c))
            {
                free(stack);
                return 0; // 括号不匹配
            }
            top--; // 弹出栈顶
        }
    }

    // 最后检查栈是否为空
    int result = (top == STACK_EMPTY);
    free(stack);
    return result;
}

// 反转字符串（处理括号翻转）
void reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
        if (str[len - i - 1] == '(')
            str[len - i - 1] = ')';
        else if (str[len - i - 1] == ')')
            str[len - i - 1] = '(';
    }
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 把中缀表达式转换为前缀表达式
char *infix_to_prefix(char *infix)
{
    char temp[MAX];
    strcpy(temp, infix);
    reverse(temp);
    int len = strlen(infix);
    char *prefix = (char *)malloc(2 * len * sizeof(char));
    char *stack = (char *)malloc(len * sizeof(char));
    int top = -1, j = 0;

    for (int i = 0; i < len; i++)
    {
        char c = temp[i];
        if (c == ' ')
            continue;

        if (isdigit(c))
        {
            // 处理连续数字
            while (i < len && isdigit(temp[i]))
            {
                prefix[j++] = temp[i++];
            }
            i--;               // 补偿for循环的i++
            prefix[j++] = ' '; // 添加分隔符
        }
        else if (c == ')')
        {
            // 反转后的右括号视为左括号
            stack[++top] = c;
        }
        else if (c == '(')
        {
            // 反转后的左括号视为右括号
            while (top != -1 && stack[top] != ')')
            {
                prefix[j++] = stack[top--];
            }
            top--; // 弹出对应的右括号
        }
        else
        {
            // 运算符处理   当栈顶优先级大于当前优先级，则弹出栈顶元素
            while (top != -1 && precedence(c) < precedence(stack[top]))
            {
                prefix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    // 弹出栈中剩余运算符
    while (top != -1)
    {
        prefix[j++] = stack[top--];
    }

    prefix[j] = '\0';
    reverse(prefix); // 反转结果得到前缀表达式
    free(stack);
    return prefix;
}

int main()
{
    printf("请输入中缀表达式：");
    char infix_expression[MAX];
    scanf("%s", infix_expression);
    // 检测中缀表达式是否合法
    if (check_infix_expression(infix_expression) == 0)
    {
        printf("中缀表达式不合法！\n");
        return 0;
    }
    // 把中缀表达式转换为前缀表达式
    char *prefix_expression;
    prefix_expression = infix_to_prefix(infix_expression);
    // 从右向左扫描前缀表达式，从左向右出栈
    // 初始化一个栈
    int stack[MAX];
    int top = -1;
    for (int i = strlen(prefix_expression) - 1; i >= 0; i--)
    {
        char c = prefix_expression[i];
        
        if (isdigit(c))
        {
            int num = 0;
            while (i >= 0 && isdigit(prefix_expression[i]))
            {
                num = num * 10 + (prefix_expression[i--] - '0');
            }
            i++; // 补偿i--的过度移动
            stack[++top] = num;
        }
        else
        {
            int num1 = stack[top--];
            int num2 = stack[top--];
            switch (c)
            {
            case '+':
                stack[++top] = num1 + num2;
                break;
            case '-':
                stack[++top] = num1 - num2;
                break;
            case '*':
                stack[++top] = num1 * num2;
                break;
            case '/':
                if (num2 == 0)
                {
                    printf("除数不能为0！");
                    exit(1);
                }
                stack[++top] = num1 / num2;
                break;
            }
        }
    }
    printf("表达式结果为：%d\n", stack[top]);
    return 0;
}
