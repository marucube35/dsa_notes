#include "Sorting.h"

void selectionSortExperiment(int arr[], int n, long long &comparison)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1 && ++comparison; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n && ++comparison; j++)
            if (arr[j] < arr[min_idx] && ++comparison)
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(arr[min_idx], arr[i]);
    }
}
