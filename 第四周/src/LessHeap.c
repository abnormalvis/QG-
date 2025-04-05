// 大根堆的实现
#include <stdio.h>
#include <stdlib.h>
typedef int E;
typedef struct LessHeap
{
    E *arr;
    int size;
    int capacity;
} *Heap;

_Bool initHeap(Heap heap)
{ // 初始化都是老套路了，不多说了
    heap->size = 0;
    heap->capacity = 10;
    heap->arr = malloc(sizeof(E) * heap->capacity);
    return heap->arr != NULL;
}

_Bool insert(Heap heap, E element)
{
    if (heap->size == heap->capacity)
        return 0;             // 满了就不处理了，主要懒得写扩容了
    int index = ++heap->size; // 先计算出要插入的位置，注意要先自增，因为是从1开始的
    // 然后开始向上堆化，直到符合规则为止
    while (index > 1 && element > heap->arr[index / 2])
    {
        heap->arr[index] = heap->arr[index / 2];
        index /= 2;
    }
    // 现在得到的index就是最终的位置了
    heap->arr[index] = element;
    return 1;
}
E delete(Heap heap)
{
    E max = heap->arr[1], e = heap->arr[heap->size--];
    int index = 1;
    while (index * 2 <= heap->size)
    {                          // 跟上面一样，开找，只不过是从上往下找
        int child = index * 2; // 先找到左孩子
        // 看看右孩子和左孩子哪个大，先选一个大的出来
        if (child < heap->size && heap->arr[child] < heap->arr[child + 1])
            child += 1;
        if (e >= heap->arr[child])
            break; // 如果子结点都不大于新结点，那么说明就是这个位置，结束就行了
        else
            heap->arr[index] = heap->arr[child]; // 否则直接堆化，换上去
        index = child;                           // 最后更新一下index到下面去
    }
    heap->arr[index] = e; // 找到合适位置后，放进去就行了
    return max;
}
void printHeap(Heap heap)
{
    for (int i = 1; i <= heap->size; ++i)
        printf("%d ", heap->arr[i]);
}

int main()
{
    struct LessHeap heap;
    printf("准备入队...");
    initHeap(&heap);
    insert(&heap, 5);
    insert(&heap, 2);
    insert(&heap, 3);
    insert(&heap, 7);
    insert(&heap, 6);

    printHeap(&heap);
    printf("\n出队：\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", delete (&heap));
    }
    printf("\n");
    free(heap.arr); // 释放内存
    return 0;
}