#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 1000

typedef struct tnode
{
    int num;
    struct tnode *left;
    struct tnode *right;
} Node;

int getword(char *word, int lim);
struct tnode *addtree(Node *, int num);
void printTree(Node *);
Node *invertTree(Node *);
struct tnode *talloc(void);


int main(int argc, char const *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (isnumber(word[0]))
            root = addtree(root, atoi(word));
    }

    printf("-----before invert-----\n");
    printTree(root);
    invertTree(root);
    printf("-----after invert-----\n");
    printTree(root);

    return 0;
}

struct tnode *addtree(Node *node, int num)
{
    int cond;

    if (node == NULL)
    {
        node = talloc();
        node->num = num;
        node->left = node->right = NULL;
    }
    else if (num < node->num)
        node->left = addtree(node->left, num);
    else
        node->right = addtree(node->right, num);
    return node;
}

struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(Node));
}

void printTree(Node *node)
{
    if (node == NULL) return;
    printTree(node->left);
    printf("%i\n", node->num);
    printTree(node->right);
}

Node *invertTree(Node *node)
{
    if (node == NULL) return NULL;
    Node *left = invertTree(node->left);
    Node *right = invertTree(node->right);

    node->left = right;
    node->right = left;

    return node;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isnumber(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
    {
        if (!isnumber((*w = getch())))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';

    return word[0];
}

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many chars");
    else
        buf[bufp++] = c;
}