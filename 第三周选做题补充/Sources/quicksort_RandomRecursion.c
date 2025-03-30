#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 用于划分数组，返回枢轴位置
int partition(int arr[], int low, int high)
{
    int pivot = arr[low]; // 选择第一个元素作为枢轴
    int i = low;          // 初始化指针i、j
    int j = high;

    while (i < j)
    {
        // 从右向左寻找第一个小于枢轴的元素
        while(i < j && arr[j] >= pivot)     // 找到第一个小于枢轴的元素
            j--;
        arr[i] = arr[j];
        while(i < j && arr[i] <= pivot)     // 找到第一个大于枢轴的元素
            i++;
        arr[j] = arr[i];
    }
    arr[i] = pivot;                         // 将枢轴放到正确的位置
    return i;                               // 返回枢轴位置
}

void quickSortRecursive(int arr[], int low, int high)
{
    if (low < high)
    {
        // 随机选择枢轴
        int random = low + rand() % (high - low + 1);
        swap(&arr[low], &arr[random]);
        int pivotIndex = partition(arr, low, high);     // 划分数组

        // 三枢轴优化：将数组分为三部分，减少递归深度
        int left = pivotIndex - 1;                      // 找到第一个小于枢轴的元素
        int right = pivotIndex + 1;                     // 找到第一个大于枢轴的元素

        while (left >= low && arr[left] == arr[pivotIndex])
            // 如果左指针和枢轴元素相等，继续向左寻找
            left--;
        while (right <= high && arr[right] == arr[pivotIndex])
            // 如果右指针和枢轴元素相等，继续向右寻找
            right++;
        // 递归调用
        quickSortRecursive(arr, low, left);
        quickSortRecursive(arr, right, high);
    }
}

int main()
{
    int arr[] = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    srand(time(0)); // 初始化随机数种子

    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSortRecursive(arr, 0, size - 1);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}