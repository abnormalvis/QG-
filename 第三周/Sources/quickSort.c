#include <stdio.h>
#include <quickSort.h>
// 快速排序
// 本质是分治法 + 递归
void quickSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int i = left, j = right, x = arr[left];
        while (i < j)
        {
            while (i < j && arr[j] >= x)
                j--;
            if (i < j)
                arr[i++] = arr[j];
            while (i < j && arr[i] < x)
                i++;
        }
    }
}