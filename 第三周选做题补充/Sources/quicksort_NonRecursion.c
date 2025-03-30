#include <stdio.h>
#include <stdlib.h>

//  非递归快速排序
void quickSortNonRecursive(int arr[], int size)
{
    int stack[size][2];             // 栈用于保存分区的左右边界
    int top = -1;                   // 栈顶指针
    int left, right, pivot, i, j;   
    // 初始化栈
    stack[++top][0] = 0;         
    stack[top][1] = size - 1;
    while (top >= 0)
    {
        // 弹出栈顶元素
        left = stack[top][0];
        right = stack[top--][1];

        if (left >= right)         // 如果分区大小小于等于1，则跳过此分区
            continue;

        // 选择枢轴并分区
        pivot = arr[left];  
        i = left;   
        j = right;

        while (i < j)
        {
            while (i < j && arr[j] >= pivot)
                // 如果右指针指向的元素大于枢轴，则右指针左移
                j--;
            arr[i] = arr[j];
            while (i < j && arr[i] <= pivot)
                // 如果左指针指向的元素小于枢轴，则左指针右移
                i++;
            arr[j] = arr[i];
        }
        arr[i] = pivot;

        // 将子分区压入栈
        stack[++top][0] = left;     // 左边界
        stack[top][1] = i - 1;      // 右边界
        stack[++top][0] = i + 1;    // 左边界
        stack[top][1] = right;      // 右边界
    }
}

int main()
{
    // 测试数组
    int arr[] = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    quickSortNonRecursive(arr, size);
    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}