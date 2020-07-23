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

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
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

