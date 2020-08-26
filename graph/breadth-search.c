#include <stdio.h>
#include <stdlib.h>

#define VERTICESNUM 10

typedef struct _adjNode {
    int vertex;
    struct _adjNode *next;
} AdjNode;

typedef struct _queueNode 
{
    int data;
    struct _queueNode *next;    
} QueueNode;

typedef struct _queue
{
    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct _graph
{
    int verticeNum;
    int *visited;
    AdjNode **adjList;
} Graph;

Graph *createGraph(int verticeNum);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
void addEdge(Graph *graph, int src, int dest);
void bfs(Graph *graph, int s);

int main(int argc, char const *argv[])
{
    Graph *graph = createGraph(VERTICESNUM);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 2, 7);
    addEdge(graph, 2, 8);
    addEdge(graph, 3, 2);
    addEdge(graph, 3, 9);
    addEdge(graph, 9, 1);
    
    bfs(graph, 0);

    return 0;
}

Graph *createGraph(int verticeNum)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->verticeNum = VERTICESNUM;
    graph->adjList = (AdjNode **)malloc(sizeof(AdjNode *) * VERTICESNUM);
    graph->visited = (int *)malloc(sizeof(int) * VERTICESNUM);

    for (size_t i = 0; i < verticeNum; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
    AdjNode *newNode = (AdjNode *)malloc(sizeof(AdjNode));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Travels all level vertices
void bfs(Graph *graph, int s)
{
    void addEdgeToQueue(Queue *queue, AdjNode *adjNode);
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;

    addEdgeToQueue(&queue, graph->adjList[s]);
    while ((s = dequeue(&queue)) >= 0)
    {
        if (graph->visited[s]) continue;
        
         graph->visited[s] = 1;
         printf("%d\n", s);
         addEdgeToQueue(&queue, graph->adjList[s]);
    }
}

void addEdgeToQueue(Queue *queue, AdjNode *adjNode)
{
    while (adjNode != NULL)
    {
        enqueue(queue, adjNode->vertex);
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
