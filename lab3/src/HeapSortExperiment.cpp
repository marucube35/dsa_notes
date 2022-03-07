#include "Sorting.h"

void heapifyExperiment(int *arr, int n, int i, long long &count_compare)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if ((++count_compare && l < n) && (++count_compare && arr[l] > arr[largest]))
        largest = l;

    if ((++count_compare && r < n) && (++count_compare && arr[r] > arr[largest]))
        largest = r;

    if (++count_compare && largest != i)
    {
        swap(arr[i], arr[largest]);

        heapifyExperiment(arr, n, largest, count_compare);
    }
}

void heapSortExperiment(int *arr, int n, long long &count_compare)
{
    for (int i = n / 2 - 1; ++count_compare && i >= 0; i--)
    {
        heapifyExperiment(arr, n, i, count_compare);
    }

    for (int i = n - 1; ++count_compare && i > 0; i--)
    {
        swap(arr[0], arr[i]);

        heapifyExperiment(arr, i, 0, count_compare);
    }
}
