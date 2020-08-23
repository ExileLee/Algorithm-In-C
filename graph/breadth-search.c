#include <stdio.h>
#include <stdlib.h>

#define VERTICESCOUNT 10

typedef struct _adjNode {
    int accountId;
    int isVip;
    struct _adjNode *next;
} AdjNode;

typedef struct _queueNode {
    int data;
    struct _queueNode *next;    
} QueueNode;

typedef struct _queue
{
    QueueNode *head;
    QueueNode *tail;
} Queue;

void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
void addEdge(AdjNode **adjList, int src, int dest);
void bfs(int s);

AdjNode *adjList[VERTICESCOUNT];

int main(int argc, char const *argv[])
{
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 0, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 1, 5);
    addEdge(adjList, 2, 6);
    addEdge(adjList, 2, 7);
    addEdge(adjList, 2, 8);
    addEdge(adjList, 3, 2);
    addEdge(adjList, 3, 9);
    addEdge(adjList, 9, 1);
    
    bfs(0);

    return 0;
}

void addEdge(AdjNode **adjList, int src, int dest)
{
    AdjNode *newNode = (AdjNode *)malloc(sizeof(AdjNode));
    newNode->accountId = dest;
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

// Travels all level vertices
void bfs(int s)
{
    void addEdgeToQueue(Queue *queue, AdjNode *adjNode);
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;

    int visived[VERTICESCOUNT];
    for (size_t i = 0; i < VERTICESCOUNT; i++)
        visived[i] = 0;
    
    addEdgeToQueue(&queue, adjList[s]);
    while ((s = dequeue(&queue)) >= 0)
    {
        if (visived[s]) continue;
        
         visived[s] = 1;
         printf("%d\n", s);
         addEdgeToQueue(&queue, adjList[s]);
    }

}

void addEdgeToQueue(Queue *queue, AdjNode *adjNode)
{
    while (adjNode != NULL)
    {
        enqueue(queue, adjNode->accountId);
        adjNode = adjNode->next;
    }
}

void enqueue(Queue *queue, int data)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    if (queue->tail != NULL)
        queue->tail->next = node;
    else
        queue->head = node;        

    queue->tail = node;    
}

int dequeue(Queue *queue)
{
    QueueNode *popNode = queue->head;
    if (!popNode)
        return -1;

    int data = popNode->data;
    queue->head = popNode->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    free((void *)popNode);    

    return data;
}
