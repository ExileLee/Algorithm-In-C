#include <stdio.h>
#include <stdlib.h>

#define max(a,b) \
  ({ __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; })

typedef struct _minPriorityQueue {
    int heapSize;
    int heapCapacity;
    int *heap;
} MinPriorityQueue;

MinPriorityQueue *initialPriorityQeueue(int num, int *keys);
void sink(MinPriorityQueue *pq, int i);
void swim(MinPriorityQueue *pq, int i);
void swap(int *, int *);
void heapify(MinPriorityQueue *pq);
void add(MinPriorityQueue *pq, int key);
int poll(MinPriorityQueue *pq);
int peek(MinPriorityQueue *pq);
int isEmpty(MinPriorityQueue *pq);

int main(int argc, char const *argv[])
{
    int keys[] = {5, 4, 1, 7, 2, 7, 3, 9, 10, 22, 5, 12, 15, 63, 12};
    int size = sizeof keys / sizeof keys[0];
    MinPriorityQueue *pq = initialPriorityQeueue(size, keys);

    while (!isEmpty(pq))
        printf("%d ", poll(pq));

    printf("\n");    

    return 0;
}

MinPriorityQueue *initialPriorityQeueue(int num, int *keys)
{
    MinPriorityQueue *pq = (MinPriorityQueue *)malloc(sizeof(MinPriorityQueue));
    pq->heapSize = num;
    pq->heapCapacity = num;
    pq->heap = (int *)malloc(sizeof(int) * num);
    for (size_t i = 0; i < num; i++)
        pq->heap[i] = keys[i];

    heapify(pq);

    return pq;    
}

void heapify(MinPriorityQueue *pq)
{
    for (int i = max(0, (pq->heapSize / 2) - 1); i >= 0; i--)
        sink(pq, i);
}

void sink(MinPriorityQueue *pq, int i)
{
    while (1)
    {
        int left = (i * 2) + 1;
        int right = (i *2 ) + 2;
        int smallest = left;

        if (right < pq->heapSize && pq->heap[right] < pq->heap[smallest])
            smallest = right;

        if (left >= pq->heapSize || pq->heap[smallest] > pq->heap[i]) break;

        swap(&pq->heap[i], &pq->heap[smallest]);
        i = smallest;
    }
}

void swim(MinPriorityQueue *pq, int i)
{
    int parent = (i-1) / 2;

    while (i > 0 && pq->heap[parent] > pq->heap[i])
    {
        swap(&pq->heap[parent], &pq->heap[i]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void swap(int *s, int *t)
{
    int tmp = *s;
    *s = *t;
    *t = tmp;
}

int poll(MinPriorityQueue *pq)
{
    int rootKey = pq->heap[0];

    swap(&pq->heap[0], &pq->heap[pq->heapSize-1]);
    pq->heapSize--;
    sink(pq, 0);

    return rootKey;
}

int peek(MinPriorityQueue *pq)
{
    return pq->heap[0];
}

int isEmpty(MinPriorityQueue *pq)
{
    return pq->heapSize < 1;
}

void add(MinPriorityQueue *pq, int key)
{
    if (pq->heapSize >= pq->heapCapacity)
        return;
    int last = pq->heapSize-1;    
    pq->heap[last] = key;    

    swim(pq, last);
}
