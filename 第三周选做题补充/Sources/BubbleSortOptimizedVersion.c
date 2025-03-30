#include <stdio.h>
// 优化冒泡排序函数
void optimizedBubbleSort(int arr[], int size)
{
    int i, j, temp;
    int swapped;

    // 外层循环控制整个排序过程
    for (i = 0; i < size - 1; i++)
    {
        swapped = 0;

        // 从左到右遍历数组，进行相邻元素比较和交换
        // 优化1：如果某次遍历没有发生交换，说明数组已经有序
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // 交换相邻两个元素
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // 如果没有发生交换，提前退出
        if (!swapped)
            break;

        // 从右到左遍历数组，进行相邻元素比较和交换
        // 优化3：交替从左到右和从右到左遍历
        swapped = 0;
        for (j = size - i - 2; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                // 交换相邻两个元素
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                swapped = 1;
            }
        }

        // 如果没有发生交换，提前退出
        if (!swapped)
            break;
    }
}
int main()
{
    int arr[] = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    optimizedBubbleSort(arr, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}