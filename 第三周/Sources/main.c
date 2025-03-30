#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "insertSort.h"
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
int main()
{
    // Test array sizes
    int sizes[] = {10000, 50000, 200000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_tests; i++)
    {
        int n = sizes[i];
        int *arr = (int *)malloc(sizeof(int) * n);

        // Generate random numbers
        for (int j = 0; j < n; j++)
        {
            arr[j] = rand() % 1000000;
        }

        // Measure sorting time
        clock_t start = clock();
        insertSort(arr); // Pass array size as second parameter
        clock_t end = clock();

        printf("n = %d insertSort time: %.2f ms\n",
               n, (double)(end - start) * 1000 / CLOCKS_PER_SEC);

        free(arr);
    }

    return 0;
}