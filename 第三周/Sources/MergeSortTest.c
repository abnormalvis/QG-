#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int tmp[], int start, int mid, int end)
{
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end)
    {
        if (arr[i] <= arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        tmp[k++] = arr[i++];
    }
    while (j <= end)
    {
        tmp[k++] = arr[j++];
    }
    for (i = start; i <= end; i++)
    {
        arr[i] = tmp[i];
    }
}

void mergeSort(int arr[], int tmp[], int start, int end)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    mergeSort(arr, tmp, start, mid);
    mergeSort(arr, tmp, mid + 1, end);
    merge(arr, tmp, start, mid, end);
}

void mergeSortWrapper(int arr[], int n)
{
    int *tmp = (int *)malloc(n * sizeof(int));
    mergeSort(arr, tmp, 0, n - 1);
    free(tmp);
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
    testSort(10000, mergeSortWrapper);
    testSort(50000, mergeSortWrapper);
    testSort(200000, mergeSortWrapper);
    return 0;
}