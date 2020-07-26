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

typedef LinkedList Stack;

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

void initailizeStack(Stack *);
void push(Stack *, void *);
void *pop(Stack *);

int main(int argc, char const *argv[])
{
    Stack stack;

    initailizeStack(&stack);

    Album nevermind;
    nevermind.title = "Nevermind";
    nevermind.artist = "nirnanva";

    Album isthisit;
    isthisit.title = "Is This it";
    isthisit.artist = "The Strokes";

    Album okcomputer;
    okcomputer.title = "Ok Computer";
    okcomputer.artist = "Radiohead";

    push(&stack, &nevermind);
    push(&stack, &isthisit);
    push(&stack, &okcomputer);

    Node *current = stack.head;
    void *data;
    do
    {
        data = pop(&stack);
        if (data != NULL)
            printf("%s\n", ((Album*)data)->title);
    } while(data != NULL);

    return 0;
}

void initailizeStack(Stack *stack)
{
    initailizeList(stack);
}

void push(Stack *stack, void *node)
{
    addHead(stack, node);
}

void *pop(Stack *stack)
{
    Node *node = stack->head;
    
    if (stack->head == NULL)
        return NULL;
    else if (stack->tail == node)
    {
        stack->head = stack->tail = NULL;
        void *data = node->data;
        free(node);
        return data;
    }
    else
    {
        stack->head = stack->head->next;
        void *data = node->data;
        free(node);
        return data;
    }
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