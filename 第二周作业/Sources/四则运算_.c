#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX 100 // ջ��󳤶�
/*
���� ���� �������  ����� +-
��->ǰ ���ŷ�ǰ��
��->�� ���ŷź���
ǰ->�� ��������ɨ������� �������ҳ�ջ
��->�� ��������ɨ������� ���������ջ
*/

// ��һ���ַ��������������������׺���ʽ Ȼ�����׺���ʽת��Ϊǰ׺���ʽ�����Ű�ǰ׺���ʽ��������ɨ�裬�������ҳ�ջ

#define STACK_EMPTY (-1)

// ��������������ַ��Ƿ�Ϊ�Ϸ������������
int is_valid_char(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}' ||
           c == '[' || c == ']' || c == '+' || c == '-' ||
           c == '*' || c == '/' || c == ' ' || isdigit(c);
}

// ������������������Ƿ�ƥ��
int is_matching_pair(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

// �����׺���ʽ�Ƿ�Ϸ�
int check_infix_expression(char *infix_expression)
{
    if (infix_expression == NULL || infix_expression[0] == '\0')
    {
        return 0; // �����ָ�����ַ���
    }

    size_t len = strlen(infix_expression);
    if (len == 0)
    {
        return 1; // ���ַ�����Ϊ�Ϸ�
    }

    // ��̬����ջ����СΪ�ַ�������
    int *stack = (int *)malloc(len * sizeof(int));
    if (stack == NULL)
    {
        return 0; // �ڴ����ʧ��
    }

    int top = STACK_EMPTY; // ջ��ָ���ʼ��

    for (size_t i = 0; i < len; i++)
    {
        char c = infix_expression[i];

        // ����ַ��Ϸ���
        if (!is_valid_char(c))
        {
            free(stack);
            return 0; // �Ƿ��ַ�
        }

        // ���������ţ�ѹ��ջ
        if (c == '(' || c == '{' || c == '[')
        {
            stack[++top] = c;
        }
        // ���������ţ�����ջ�����ƥ��
        else if (c == ')' || c == '}' || c == ']')
        {
            if (top == STACK_EMPTY || !is_matching_pair(stack[top], c))
            {
                free(stack);
                return 0; // ���Ų�ƥ��
            }
            top--; // ����ջ��
        }
    }

    // �����ջ�Ƿ�Ϊ��
    int result = (top == STACK_EMPTY);
    free(stack);
    return result;
}

// ��ת�ַ������������ŷ�ת��
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

// ����׺���ʽת��Ϊǰ׺���ʽ
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
            // ������������
            while (i < len && isdigit(temp[i]))
            {
                prefix[j++] = temp[i++];
            }
            i--;               // ����forѭ����i++
            prefix[j++] = ' '; // ��ӷָ���
        }
        else if (c == ')')
        {
            // ��ת�����������Ϊ������
            stack[++top] = c;
        }
        else if (c == '(')
        {
            // ��ת�����������Ϊ������
            while (top != -1 && stack[top] != ')')
            {
                prefix[j++] = stack[top--];
            }
            top--; // ������Ӧ��������
        }
        else
        {
            // ���������   ��ջ�����ȼ����ڵ�ǰ���ȼ����򵯳�ջ��Ԫ��
            while (top != -1 && precedence(c) < precedence(stack[top]))
            {
                prefix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    // ����ջ��ʣ�������
    while (top != -1)
    {
        prefix[j++] = stack[top--];
    }

    prefix[j] = '\0';
    reverse(prefix); // ��ת����õ�ǰ׺���ʽ
    free(stack);
    return prefix;
}

int main()
{
    printf("��������׺���ʽ��");
    char infix_expression[MAX];
    scanf("%s", infix_expression);
    // �����׺���ʽ�Ƿ�Ϸ�
    if (check_infix_expression(infix_expression) == 0)
    {
        printf("��׺���ʽ���Ϸ���\n");
        return 0;
    }
    // ����׺���ʽת��Ϊǰ׺���ʽ
    char *prefix_expression;
    prefix_expression = infix_to_prefix(infix_expression);
    // ��������ɨ��ǰ׺���ʽ���������ҳ�ջ
    // ��ʼ��һ��ջ
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
            i++; // ����i--�Ĺ����ƶ�
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
                    printf("��������Ϊ0��");
                    exit(1);
                }
                stack[++top] = num1 / num2;
                break;
            }
        }
    }
    printf("���ʽ���Ϊ��%d\n", stack[top]);
    return 0;
}
