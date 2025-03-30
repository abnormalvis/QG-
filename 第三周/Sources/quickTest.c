#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 快速排序实现
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
            if (i < j)
                arr[j--] = arr[i];
        }
        arr[i] = x;                   // 将基准值放回中间位置
        quickSort(arr, left, i - 1);  // 递归排序左子数组
        quickSort(arr, i + 1, right); // 递归排序右子数组
    }
}

// 快速排序的封装函数
void quickSortWrapper(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}

// 测试排序函数
void testSort(int n, void (*sortFunc)(int[], int))
{
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000000;
    }
    clock_t start = clock();
    sortFunc(arr, n);
    printf("n=%d  time: %ld ms\n", n, (clock() - start) * 1000 / CLOCKS_PER_SEC);
    free(arr);
}

int main()
{
    srand(time(NULL)); // 初始化随机数种子
    testSort(100000, quickSortWrapper);
    testSort(500000, quickSortWrapper);
    testSort(2000000, quickSortWrapper);
    return 0;
}