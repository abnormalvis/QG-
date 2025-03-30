#include "insertSort.h"
#include <stdio.h>
// 插入排序
void insertSort(int arr[])
{
    int size = sizeof(arr) / sizeof(int);
    for (int i = 1; i < size; ++i)
    {                            // 从第二个元素开始看
        int j = i, tmp = arr[i]; // j直接变成i，因为前面的都是有序的了，tmp相当于是抽出来的牌暂存一下
        while (j > 0 && arr[j - 1] > tmp)
        {                        // 只要j>0并且前一个还大于当前待插入元素，就一直往前找
            arr[j] = arr[j - 1]; // 找的过程中需要不断进行后移操作，把位置腾出来
            j--;
        }
        arr[j] = tmp; // j最后在哪个位置，就是是哪个位置插入
    }
}