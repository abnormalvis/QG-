#include <stdio.h>
#include <stdlib.h>

// 判断链表是否成环
typedef int E;

struct List
{
    E *array;
    int capacity;
    int size;
};

typedef struct List *ArrayList;

_Bool isCircle(ArrayList list)
{
    if (list->size == 0)
        return 0;
    int slow = 0, fast = 0;   // 快慢指针
    while (fast < list->size) //  快指针未到达链表尾部
    {
        slow++;           // 慢指针走一步
        fast += 2;        // 快指针走两步
        if (slow == fast) // 快慢指针相遇，说明链表成环
            return 1;     // 1 --> 成环 0 --> 未成环
    }
    return 0;
}

_Bool initList(ArrayList list)
{
    list->capacity = malloc(sizeof(int) * list->capacity);
    if (list->array == NULL) // 分配内存成功
        return 0;
    list->size = 0;
    return 1;
}
//
// bool insertJudge(ArrayList list, int index)
//{
//	if (index < 1 || index > list->size + 1)
//		return 0;
//	return 1;   // 1 --> 可以插入 0 --> 不可以插入
//}

// 插入元素  要判断插入的范围是否在[1, size + 1]
_Bool insertElement(ArrayList list, E element, int index)
{
    if (index < 1 || index > list->size + 1) // 不符合插入条件
        return 0;
    if (list->size == list->capacity)
    {
        int newCapacity = list->capacity + (list->capacity >> 1);
        E *newArray = realloc(list->array, newCapacity * sizeof(E));
        if (newArray == NULL)
            return 0;
        list->array = newArray;
        list->capacity = newCapacity;
    }
    for (int i = list->size; i > list->size - 1; --i)
        list->array[i] = list->array[i - 1];
    list->array[index - 1] = element;
    list->size++;

    return 1;
}

int main()
{
    ArrayList list;
    // 初始化链表
    initList(list);
    insertElement(list, 1, 1);
    insertElement(list, 2, 2);
    insertElement(list, 3, 3);
    insertElement(list, 4, 4);
    // 判断链表是否成环
    if (isCircle(list))
        printf("链表成环\n");
    else
        printf("链表未成环\n");
    return 0;
}