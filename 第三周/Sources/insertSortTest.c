#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSort(int arr[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        int j = i, tmp = arr[i];
        while (j > 0 && arr[j - 1] > tmp)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = tmp;
    }
}

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
    testSort(10000, insertSort);
    testSort(50000, insertSort);
    testSort(200000, insertSort);
    return 0;
}