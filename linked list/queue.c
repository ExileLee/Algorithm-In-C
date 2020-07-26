#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    void *data;
    struct _node *next;
} Node;

typedef struct _linkedList {
    Node *head;
    Node *tail;
    Node *current;
} LinkedList;

typedef LinkedList Queue;

typedef struct _album {
    char *title;
    char *artist;
} Album;

typedef int (*COMPARE)(void*, void*);
typedef void (*DISPLAY)(void*);

void initailizeList(LinkedList*);
void addHead(LinkedList*, void*);
void addTail(LinkedList*, void*);
void delete(LinkedList*, Node*);
Node *getNode(LinkedList*, COMPARE, void*);
void displayLinkedList(LinkedList*, DISPLAY);

void initailizeQueue(Queue *);
void enqueue(Queue *, void *);
void *dequeue(Queue *);

int main(int argc, char const *argv[])
{
    Queue queue;

    initailizeQueue(&queue);

    Album nevermind;
    nevermind.title = "Nevermind";
    nevermind.artist = "nirnanva";

    Album isthisit;
    isthisit.title = "Is This it";
    isthisit.artist = "The Strokes";

    Album okcomputer;
    okcomputer.title = "Ok Computer";
    okcomputer.artist = "Radiohead";

    enqueue(&queue, &nevermind);
    enqueue(&queue, &isthisit);
    enqueue(&queue, &okcomputer);

    Node *current = queue.head;
    void *data;
    do
    {
        data = dequeue(&queue);
        if (data != NULL)
            printf("%s\n", ((Album*)data)->title);
    } while(data != NULL);

    return 0;
}

void initailizeQueue(Queue *queue)
{
    initailizeList(queue);
}

void enqueue(Queue *queue, void *node)
{
    addHead(queue, node);
}

void *dequeue(Queue *queue)
{
    Node *tmp = queue->head;
    void *data;

    if (queue->head == NULL)
        data = NULL;
    else if (queue->head == queue->tail)
    {
        queue->head = queue->tail = NULL;
        data = tmp->data;
        free(tmp);
    }   
    else
    {
        while (tmp->next != queue->tail)
            tmp = tmp->next;
        queue->tail = tmp;
        tmp = tmp->next;
        queue->tail->next = NULL;
        data = tmp->data;
        free(tmp);    
    }

    return data;
}

void initailizeList(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
}

void addHead(LinkedList *list, void *data)
{
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    if (list->head == NULL)
    {
        list->tail = node;
        node->next = NULL;
    }
    else
        node->next = list->head;
    
    list->head = node;
}

void addTail(LinkedList *list, void *data)
{
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL)
        list->head = node;
    else
        list->tail->next = node;
    list->tail = node;    
}

Node *getNode(LinkedList *list, COMPARE compare, void *data)
{
    Node *node = list->head;
    while (node != NULL)
    {
        if (compare(node->data, data) == 0)
            return node;
        node = node->next;
    }

    return NULL;
}

void delete(LinkedList *list, Node *node)
{
    if (node == list->head)
    {
        if (list->head->next == NULL)
            list->head = list->tail = NULL;
        else
            list->head = list->head->next;
            
    }
    else
    {
        Node *prev = list->head;

        while (prev != NULL && prev->next != node)
            prev = prev->next;

        if (prev != NULL)
            prev->next = node->next;
    }
    
    free(node);
}

void displayLinkedList(LinkedList *list, DISPLAY display)
{
    printf("\n----------Linked List----------");
    for (Node *current = list->head; current != NULL; current = current->next)
        display(current->data);
}