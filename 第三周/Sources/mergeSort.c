#include <stdio.h>
#include <mergeSort.h>

// 归并排序
void merge(int arr[], int tmp[], int left, int leftEnd, int right, int rightEnd)
{
    int i = left, size = rightEnd - left + 1; // 这里需要保存一下当前范围长度，后面使用
    while (left <= leftEnd && right <= rightEnd)
    {                                // 如果两边都还有，那么就看哪边小，下一个就存哪一边的
        if (arr[left] <= arr[right]) // 如果左边的小，那么就将左边的存到下一个位置（这里i是从left开始的）
            tmp[i++] = arr[left++];  // 操作完后记得对i和left都进行自增
        else
            tmp[i++] = arr[right++];
    }
    while (left <= leftEnd) // 如果右边看完了，只剩左边，直接把左边的存进去
        tmp[i++] = arr[left++];
    while (right <= rightEnd) // 同上
        tmp[i++] = arr[right++];
    for (int j = 0; j < size; ++j, rightEnd--) // 全部存到暂存空间中之后，暂存空间中的内容都是有序的了，此时挨个搬回原数组中（注意只能搬运范围内的）
        arr[rightEnd] = tmp[rightEnd];
}

void mergeSort(int arr[], int tmp[], int start, int end)
{ // 要进行归并排序需要提供数组和原数组大小的辅助空间
    if (start >= end)
        return;                      // 依然是使用递归，所以说如果范围太小，就不用看了
    int mid = (start + end) / 2;     // 先找到中心位置，一会分两半
    mergeSort(arr, tmp, start, mid); // 对左半和右半分别进行归并排序
    mergeSort(arr, tmp, mid + 1, end);
    merge(arr, tmp, start, mid, mid + 1, end);
    // 上面完事之后，左边和右边都是有序状态了，此时再对整个范围进行一次归并排序即可
}