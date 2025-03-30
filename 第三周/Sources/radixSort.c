#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 辅助函数：计算数组中的最大值
int findMax(int *arr, int n)
{
    if (n == 0)
        return 0; // 空数组返回 0
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// 辅助函数：执行基于某一位的计数排序
void countingSortByDigit(int *arr, int n, int exp)
{
    int output[n];       // 存储排序结果的临时数组
    int count[10] = {0}; // 计数数组

    // 统计每个数字出现的次数
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    // 修改 count 数组，使其包含实际位置信息
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将结果复制回原数组
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

// 主函数：基数排序
void radixSort(int *arr, int n)
{
    if (n == 0)
        return; // 空数组直接返回

    // 找到数组中的最大值
    int max = findMax(arr, n);

    // 对每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countingSortByDigit(arr, n, exp);
    }
}