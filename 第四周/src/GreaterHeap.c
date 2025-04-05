// 小根堆的实现实际上是大根堆的实现的一个变种
// 两种实现的区别在于比较函数的不同，小根堆的比较函数是大根堆的比较函数的相反
// 他们的数据结构的基础是二叉树，所以小根堆和大根堆的实现都是二叉树的实现
#include <stdio.h>
#include <stdlib.h>
typedef int E;
typedef struct GreaterHeap
{
    E *arr;
    int size;
    int capacity;
} *Heap;

_Bool initHeap(Heap heap)
{
    heap->size = 0;
    heap->capacity = 10;
    heap->arr = malloc(sizeof(E) * heap->capacity);
    return heap->arr != NULL;
}

_Bool insert(Heap heap, E element)
{
    if (heap->size == heap->capacity)
        return 0;
    int index = ++heap->size;
    // 修改1: 将 > 改为 < 实现小根堆向上调整
    while (index > 1 && element < heap->arr[index / 2])
    {
        heap->arr[index] = heap->arr[index / 2];
        index /= 2;
    }
    heap->arr[index] = element;
    return 1;
}

E delete(Heap heap)
{
    if (heap->size == 0)
    { // 添加空堆保护
        fprintf(stderr, "Heap is empty!\n");
        exit(EXIT_FAILURE);
    }
    E min = heap->arr[1];
    E e = heap->arr[heap->size--];
    int index = 1;
    while (index * 2 <= heap->size)
    {
        int child = index * 2;
        // 修改2: 选择更小的子节点
        if (child < heap->size && heap->arr[child] > heap->arr[child + 1])
            child += 1;
        // 修改3: 终止条件调整为 e <= 子节点
        if (e <= heap->arr[child])
            break;
        heap->arr[index] = heap->arr[child];
        index = child;
    }
    heap->arr[index] = e;
    return min;
}

void printHeap(Heap heap)
{
    for (int i = 1; i <= heap->size; ++i)
        printf("%d ", heap->arr[i]);
}

int main()
{
    struct GreaterHeap heap;
    printf("准备入队...");
    initHeap(&heap);
    insert(&heap, 5);
    insert(&heap, 2);
    insert(&heap, 3);
    insert(&heap, 7);
    insert(&heap, 6);

    printf("\n当前堆内容: ");
    printHeap(&heap);

    printf("\n出队顺序: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", delete (&heap));
    }

    free(heap.arr);
    return 0;
}