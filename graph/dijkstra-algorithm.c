#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define max(a,b) \
  ({ __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; })

#define VERTICESNUM 4

typedef struct _queueNode {
    int index;
    int key;
} QueueNode;

typedef struct _minPriorityQueue {
    int heapSize;
    int heapCapacity;
    QueueNode *heap;
} MinPriorityQueue;

typedef struct _adjNode {
    int vertex;
    int weight;
    struct _adjNode *next;
} AdjNode;

typedef struct _graph
{
    int verticeNum;
    int *visited;
    int *dist;
    int *prev;
    AdjNode **adjList;
} Graph;


Graph *createGraph(int verticeNum);
void addEdge(Graph *graph, int src, int dest, int weight);
void findShortesPath(Graph *graph, int start, int end);

int main(int argc, char const *argv[])
{
    Graph *graph = createGraph(VERTICESNUM);

    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 3, 3);
    addEdge(graph, 2, 1, 1);
    addEdge(graph, 2, 3, 6);

    findShortesPath(graph, 0, 3);

    return 0;
}

Graph *createGraph(int verticeNum)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->verticeNum = VERTICESNUM;
    graph->adjList = malloc(sizeof(AdjNode *) * VERTICESNUM);
    graph->visited = malloc(sizeof(int) * VERTICESNUM);
    graph->dist = malloc(sizeof(int) * VERTICESNUM);
    graph->prev = malloc(sizeof(int) * VERTICESNUM);

    for (size_t i = 0; i < VERTICESNUM; i++)
    {
        graph->dist[i] = INT32_MAX;
        graph->prev[i] = -1;
        graph->visited[i] = 0;
    }

    for (size_t i = 0; i < verticeNum; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight)
{
    AdjNode *newNode = (AdjNode *)malloc(sizeof(AdjNode));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    newNode->weight = weight;
    graph->adjList[src] = newNode;
}

MinPriorityQueue *initialPriorityQeueue(int num);
void add(MinPriorityQueue *pq, int index, int key);
QueueNode *poll(MinPriorityQueue *pq);
int isEmpty(MinPriorityQueue *pq);
void dijkstras(Graph *graph);

void findShortesPath(Graph *graph, int start, int end)
{
    void printPath(Graph *graph, int start, int vertex);
    dijkstras(graph);
    printPath(graph, start, end);
    
    printf("\n");
}

void printPath(Graph *graph, int start, int current)
{
    if (current < start) return;

    printPath(graph, start, graph->prev[current]);
    if (current != start)
        printf(" -> ");
    printf("\x1B[33m");
    printf("%d[%d]", current, graph->dist[current]);
    printf("\x1B[0m");
}

void dijkstras(Graph *graph)
{
    MinPriorityQueue *pq = initialPriorityQeueue(graph->verticeNum);
    add(pq, 0, 0);
    graph->dist[0] = 0;
    QueueNode *queueItem;
    int currentVertex;

    while (!isEmpty(pq))
    {
        queueItem = poll(pq);
        currentVertex= queueItem->index;
        graph->visited[currentVertex] = 1;
        if (graph->dist[currentVertex] < queueItem->key) continue;
        for (AdjNode *edge = graph->adjList[currentVertex]; edge != NULL; edge = edge->next)
        {
            if (graph->visited[edge->vertex]) continue;
            int newDist = graph->dist[currentVertex] + edge->weight;
            if (newDist < graph->dist[edge->vertex])
            {
                graph->dist[edge->vertex] = newDist;
                graph->prev[edge->vertex] = currentVertex;
                add(pq, edge->vertex, newDist);
            }
        }
    }
}

// Priority Queue
void sink(MinPriorityQueue *pq, int i);
void swim(MinPriorityQueue *pq, int i);
void swap(QueueNode *s, QueueNode *t);

MinPriorityQueue *initialPriorityQeueue(int num)
{
    MinPriorityQueue *pq = malloc(sizeof(MinPriorityQueue));
    pq->heapSize = 0;
    pq->heapCapacity = num;
    pq->heap = malloc(sizeof(QueueNode) * num);

    return pq;    
}

void sink(MinPriorityQueue *pq, int i)
{
    while (1)
    {
        int left = (i * 2) + 1;
        int right = (i *2 ) + 2;
        int smallest = left;

        if (right < pq->heapSize && pq->heap[right].key < pq->heap[smallest].key)
            smallest = right;

        if (left >= pq->heapSize || pq->heap[smallest].key > pq->heap[i].key) break;

        swap(&pq->heap[i], &pq->heap[smallest]);
        i = smallest;
    }
}

void swim(MinPriorityQueue *pq, int i)
{
    int parent = (i - 1) / 2;

    while (i > 0 && pq->heap[parent].key > pq->heap[i].key)
    {
        swap(&pq->heap[parent], &pq->heap[i]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void swap(QueueNode *s, QueueNode *t)
{
    QueueNode tmp = *s;
    *s = *t;
    *t = tmp;
}

QueueNode *poll(MinPriorityQueue *pq)
{
    QueueNode *last = &pq->heap[pq->heapSize-1];
    swap(&pq->heap[0], last);
    pq->heapSize--;
    sink(pq, 0);

    return last;
}

int isEmpty(MinPriorityQueue *pq)
{
    return pq->heapSize < 1;
}

void add(MinPriorityQueue *pq, int index, int key)
{
    if (pq->heapSize >= pq->heapCapacity)
        return;
    int last = pq->heapSize;
    pq->heapSize++;
    QueueNode data;
    data.index = index;
    data.key = key;    
    pq->heap[last] = data;    

    swim(pq, last);
}
