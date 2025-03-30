#include <countSort.h>
#include <stdio.h>

void countSort(int arr[], int len)
{
    // 输入验证
    if (arr == NULL || len <= 0)
    {
        printf("Invalid input\n");
        return;
    }

    // 创建一个临时数组用于存储修改后的值
    int temp[len];
    int isValid = 1; // 使用整数表示布尔值

    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0 || arr[i] >= len)
        {
            isValid = 0; // 标记存在非法值
            break;
        }
        temp[i] = arr[i] + 1; // 修改值存储到临时数组
    }

    if (!isValid)
    {
        printf("error\n");
        return; // 不改变原数组
    }

    // 如果所有值合法，更新原数组并打印
    for (int i = 0; i < len; i++)
    {
        arr[i] = temp[i];
        printf("%d ", arr[i]);
    }
    printf("\n"); // 打印换行符
}