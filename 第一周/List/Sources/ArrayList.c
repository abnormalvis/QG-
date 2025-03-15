#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct List
{
    E *array;
    int capacity;
    int size;
};

typedef struct List *ArrayList;

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

// 删除元素 要先判断index是否在[0, size - 1]范围内
_Bool deleteElement(ArrayList list, int index)
{
    if (index > list->size - 1 || index < 0)
        return 0;
    for (int i = index - 1; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    list->array[list->size] = 0;
    list->size--;
    return 1;
}

void printArray(ArrayList list)
{
    for (int i = 0; i < list->size; i++)
        printf("%d", list->array[i]);
    printf("\n");
}

int sizeList(ArrayList list)
{
    return list->size;
}

E *getList(ArrayList list, int index)
{
    if (index < 0 || index > list->size - 1)
        return NULL;
    return &list->array[index - 1];
}

int findList(ArrayList list, E element)
{
    for (int i = 0; i < list->size; ++i)
    {
        if (list->array[i] == list)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    struct List list;    // 初始化线性表
    if (initList(&list)) //	判断分配内存是否成功
    {
        insertElement(&list, 114, 1);
        insertElement(&list, 514, 2);
        insertElement(&list, 1919, 3);
        findList(&list, 114);
        deleteElement(&list, 2);
        printf("线性表的大小为：%d\n", sizeList(&list));
        printArray(&list);
    }
    else
    {
        printf("线性表初始化失败！");
    }
    system("pause");
    return 0;
}