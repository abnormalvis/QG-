#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 冒泡排序实现
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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
    testSort(100000, bubbleSort);
    testSort(500000, bubbleSort);
    testSort(2000000, bubbleSort);
    return 0;
}