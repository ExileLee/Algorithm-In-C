#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define HASHPRIMER 31
#define LINEMAXLENGTH 300

struct nlist {
    struct nlist *next;
    char *name;
    char *val;
};

static struct nlist *hashtable[HASHSIZE];
unsigned long hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *val);
int readline(char s[]);

int main(int argc, char *argv[])
{
    install("Punk", "Green Day");
    install("Metal", "Gun'n Roes");
    install("Britpop", "Oasis");

    char val[LINEMAXLENGTH];

    while (readline(val) > 0)
    {
        if (lookup(val) == NULL)
            printf("Not Found\n");
        else
            printf("Found\n");
    }

    return 0;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtable[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;

    return NULL;        
}

struct nlist *install(char *name, char *val)
{
    struct nlist *np;
    unsigned long hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;    
    }
    else
        free((void *)np->val);

    if ((np->val = strdup(val)) == NULL)
        return NULL;

    return np;            
}

unsigned long hash(char *s)
{
    unsigned long hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

int readline(char s[]) 
{
    int i, c, maxlen;
    i = 0;
    maxlen = LINEMAXLENGTH;

    while (i < maxlen - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}