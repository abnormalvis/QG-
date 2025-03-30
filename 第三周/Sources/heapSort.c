#include <stdio.h>
#include "heapSort.h"

// 堆调整函数
void heapify(int arr[], int n, int i)
{
    int largest = i;       // 初始化最大值为根节点
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点大于当前最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点，交换并递归调整
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// 堆排序函数
void heapSort(int arr[], int n)
{
    // 输入验证
    if (arr == NULL || n < 0)
    {
        fprintf(stderr, "Invalid input: array is NULL or size is negative.\n");
        return;
    }

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // 逐个提取元素
    for (int i = n - 1; i >= 0; i--)
    {
        // 交换根节点与最后一个节点
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 调整剩余堆
        heapify(arr, i, 0);
    }
}