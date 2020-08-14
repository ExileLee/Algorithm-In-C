#include <stdio.h>

int binarySearch(int *, int len, int number);

int main(int argc, char const *argv[])
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = binarySearch(array, 10, 3);

    printf("number 3 at %i\n", result);

    return 0;
}

int binarySearch(int *array, int len, int number)
{
    int low = 0;
    int height = len-1;
    int mid;

    while (low <= height)
    {
        mid = (low+height)/2;
        if (number > array[mid])
            low = mid + 1;
        else if (number < array[mid])
            height = mid - 1;
        else
            return mid;
    }

    return -1;
}
