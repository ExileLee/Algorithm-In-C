#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int rating;
    char *albumeName;
    struct _node *next;
} Node;

void push(Node **head, int ratting, char *albumName);
void mergeSort(Node **head);
void splitList(Node *source, Node **left, Node **right);
Node *merge(Node *left, Node *right);

int main(int argc, char const *argv[])
{
    Node *head;

    push(&head, 92, "Smells Like Teen Spirit");
    push(&head, 88, "The Black Parade");
    push(&head, 91, "Definitely Maybe");
    push(&head, 97, "Pretty Hate Machine");
    push(&head, 95, "Richard D. James");
    push(&head, 82, "Is This It");

    mergeSort(&head);

    while (head)
    {
        printf("%s: %d\n", head->albumeName, head->rating);
        head = head->next;
    }

    return 0;
}

void mergeSort(Node **head)
{
    if (*head == NULL || (*head)->next == NULL) 
        return;

    Node *left;
    Node *right;

    splitList(*head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *head = merge(left, right);
}

void splitList(Node *source, Node **left, Node **right)
{
    Node *slow = source;
    Node *fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *left = source;
    *right = slow->next;
    slow->next = NULL;
}

Node *merge(Node *left, Node *right)
{
    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;

    Node *result;

    if (left->rating <= right->rating)
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);        
    }

    return result;
}

void push(Node **head, int ratting, char *albumName)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->rating = ratting;
    node->albumeName = albumName;

    node->next = *head;
    *head = node;
}

