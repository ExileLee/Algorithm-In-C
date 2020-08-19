#include <stdio.h>

#define NUMBERCOUNT 10

void mergeSort(int *numbers, int len);

int main(int argc, char const *argv[])
{
    int array[] = {3, 55 , 7, 23, 10, 2, 1, 59, 35, 21};

    mergeSort(array, NUMBERCOUNT);

    for (size_t i = 0; i < NUMBERCOUNT; i++)
        printf("%i ", array[i]);

    return 0;
}

void mergeSort(int *arr, int len)
{
    void merge(int *left, int *right, int leftLen, int rightLen, int *target);
    if (len < 2) return;
    int mid = len/2;

    int leftLen = mid;
    int rightLen = len-mid;
    int left[leftLen];
    int right[leftLen];
    size_t i = 0;

    for (i = 0; i < mid; i++)
        left[i] = arr[i];
    for (i = mid; i < len; i++)
        right[i-mid] = arr[i];        

    mergeSort(left, leftLen);
    mergeSort(right, rightLen);

    merge(left, right, leftLen, rightLen, arr);
}

void merge(int *left, int *right, int leftLen, int rightLen, int *target)
{
    int i, j, k;
    i = j = k = 0;
    
    while (i < leftLen && j < rightLen)
    {
        if (left[i] <= right[j])
            target[k] = left[i++];
        else
            target[k] = right[j++];
        k++;
    }

    while (i < leftLen)
        target[k++] = left[i++];

    while (j < rightLen)
        target[k++] = right[j++];    

}