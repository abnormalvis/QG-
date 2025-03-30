#include <stdio.h>
#include "bubbleSort.h"

// 冒泡排序
void bubbleSort(int arr[])
{ // 每一轮都把当前轮次中的最大值放到最后
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; i < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]); // 交换两个数，使得较大的数往后移动
            }
        }
    }
}