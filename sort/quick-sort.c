#include <stdio.h>

#define ALBUMNUM 10

typedef struct _album
{
    char *title;
    int score;
} Album;

void quickSort(Album *, int left, int right);

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
        "Is This It", 95};

    quickSort(albums, 0, ALBUMNUM - 1);

    for (size_t i = 0; i < ALBUMNUM; i++)
        printf("%s: %i\n", albums[i].title, albums[i].score);

    return 0;
}

void quickSort(Album *albums, int left, int right)
{
    void swap(Album *, Album *);

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    swap(&albums[left], &albums[mid]);

    int pivot = albums[left].score;
    int last = left;

    for (size_t i = left + 1; i <= right; i++)
    {
        if (albums[i].score < pivot)
            swap(&albums[++last], &albums[i]);
    }

    swap(&albums[left], &albums[last]);
    quickSort(albums, left, last - 1);
    quickSort(albums, last + 1, right);
}

void swap(Album *album1, Album *album2)
{
    Album tmp = *album1;
    *album1 = *album2;
    *album2 = tmp;
}
