#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 1000

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *, char *);
void printtree(struct tnode *);
struct tnode *talloc(void);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int main(int argc, char const *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            root = addtree(root, word);
    }

    printtree(root);

    return 0;
}

struct tnode *addtree(struct tnode *node, char *word)
{
    int cond;

    if (node == NULL)
    {
        node = talloc();
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    }
    else if ((cond = strcmp(word, node->word)) == 0)
        node->count++;
    else if (cond < 0)
        node->left = addtree(node->left, word);
    else
        node->right = addtree(node->right, word);
    return node;
}

struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

void printtree(struct tnode *node)
{
    if (node == NULL) return;
    printtree(node->left);
    printf("%s\n", node->word);
    printtree(node->right);
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

    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
    {
        if (!isalnum((*w = getch())))
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