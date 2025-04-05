// С���ѵ�ʵ��ʵ�����Ǵ���ѵ�ʵ�ֵ�һ������
// ����ʵ�ֵ��������ڱȽϺ����Ĳ�ͬ��С���ѵıȽϺ����Ǵ���ѵıȽϺ������෴
// ���ǵ����ݽṹ�Ļ����Ƕ�����������С���Ѻʹ���ѵ�ʵ�ֶ��Ƕ�������ʵ��
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
    // �޸�1: �� > ��Ϊ < ʵ��С�������ϵ���
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
    { // ��ӿնѱ���
        fprintf(stderr, "Heap is empty!\n");
        exit(EXIT_FAILURE);
    }
    E min = heap->arr[1];
    E e = heap->arr[heap->size--];
    int index = 1;
    while (index * 2 <= heap->size)
    {
        int child = index * 2;
        // �޸�2: ѡ���С���ӽڵ�
        if (child < heap->size && heap->arr[child] > heap->arr[child + 1])
            child += 1;
        // �޸�3: ��ֹ��������Ϊ e <= �ӽڵ�
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
    printf("׼�����...");
    initHeap(&heap);
    insert(&heap, 5);
    insert(&heap, 2);
    insert(&heap, 3);
    insert(&heap, 7);
    insert(&heap, 6);

    printf("\n��ǰ������: ");
    printHeap(&heap);

    printf("\n����˳��: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d ", delete (&heap));
    }

    free(heap.arr);
    return 0;
}