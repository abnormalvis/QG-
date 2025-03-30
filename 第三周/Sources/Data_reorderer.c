#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义最大数组大小，避免越界
#define MAX_TEMP_SIZE 1000

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(int arr[], int n)
{
    if (n <= 0)
        return; // 边界检查：如果数组大小为 0 或负数，直接返回

    for (int i = 0; i < n - 1; i++)
    {                    // 外层循环控制轮次
        int swapped = 0; // 标志位，用于优化
        for (int j = 0; j < n - i - 1; j++)
        { // 内层循环进行相邻元素比较
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]); // 交换两个数
                swapped = 1;                // 发生了交换，设置标志位
            }
        }
        if (!swapped)
            break; // 如果某一轮没有发生交换，提前终止
    }
}

void Data_reader(const char *filename, int temp[], int max_size)
{
    printf("Ready to load data...\n");

    // 打开文件并检查是否成功
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return; // 返回而不退出程序，避免全局影响
    }

    int count = 0;
    int num;

    // 循环读取文件内容
    while (count < max_size && fscanf(fp, "%d", &num) == 1)
    {
        temp[count++] = num;
    }

    if (count == max_size)
    {
        printf("Warning: Array size limit reached. Some data may not be loaded.\n");
    }

    // 关闭文件
    fclose(fp);

    printf("Data loading completed. Loaded %d items.\n", count);
}
// 模版排序函数
int *sort_template(void (*sortFunc)(int[], int, int)) // 动态参数个数
{
    int data = malloc(sizeof(int) * MAX_TEMP_SIZE);
    printf("Ready to sort data...\n");
    Data_reader("data.txt", data, MAX_TEMP_SIZE);
    int n = sizeof(data) / sizeof(int);
    sortFunc(data, 0, n - 1);
    printf("Data sorting completed.\n");
    return data;
}

void Data_reorderer(int data[], int data_reordered[], int n)
{
    printf("Ready to reorder data...\n");
    sort_template(data);
    for (int i = 0; i < n; i++)
    {
        data_reordered[i] = data[n - i - 1];
    }
    printf("Data reordering completed.\n");
    free(data);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", data_reordered[i]);
    }
    printf("\n");
}

int main()
{
    int data[MAX_TEMP_SIZE];
    int data_reordered[MAX_TEMP_SIZE];
    int n = sizeof(data) / sizeof(int);
    Data_reorderer(data, data_reordered, n);
    return 0;
}