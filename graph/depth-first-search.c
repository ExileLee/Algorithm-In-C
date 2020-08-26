#include <stdio.h>
#include <stdlib.h>

#define VERTICESNUM 10

typedef struct _adjNode {
    int vertex;
    struct _adjNode *next;
} AdjNode;

typedef struct _graph
{
    int verticeNum;
    int *visited;
    AdjNode **adjList;
} Graph;

Graph *createGraph(int verticeNum);
void addEdge(Graph *graph, int src, int dest);
void dfs(Graph *graph, int vertex);

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

    dfs(graph, 0);
    
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

void dfs(Graph *graph, int vertex)
{
    graph->visited[vertex] = 1;
    printf("DFS Travel: %d\n", vertex);

    AdjNode *node = graph->adjList[vertex];

    while (node != NULL)
    {
        if (!graph->visited[node->vertex])
            dfs(graph, node->vertex);
        node = node->next;
    }
}