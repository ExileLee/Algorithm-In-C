#include <stdio.h>

#define ALBUMNUM 10

typedef struct _album {
    char *title;
    int score;
} Album;

void selectSort(Album *, int);

int main(int argc, char const *argv[])
{
    Album albums[] = {
        "Smells Like Teen Spirit", 92,
        "The Black Parade", 85,
        "OK Computer", 97,
        "Definitely Maybe", 94,
        "Pretty Hate Machine", 98,
        "On Fire", 85,
        "Blur", 91,
        "13", 82,
        "Richard D. James", 88,
        "Is This It", 95
    };

    selectSort(albums, ALBUMNUM);

    for (size_t i = 0; i < ALBUMNUM; i++)
        printf("%s: %i\n", albums[i].title, albums[i].score);

    return 0;
}

void selectSort(Album *albums, int len)
{
    int minIndex;
    void swap(Album *, Album *);
    for (size_t i = 0; i < len - 1; i++)
    {
        minIndex = i;
        for (size_t j = i+1; j < len; j++)
            if (albums[j].score < albums[minIndex].score)
                minIndex = j;

        swap(&albums[i], &albums[minIndex]);        
    }
}

void swap(Album *album1, Album *album2)
{
    Album tmp = *album1;
    *album1 = *album2;
    *album2 = tmp;
}
