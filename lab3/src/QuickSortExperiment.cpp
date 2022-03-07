#include "Sorting.h"

int partitionExperiment(int arr[], int low, int high, long long &comparison)
{
    int pivot = arr[(high + low) / 2]; // pivot
    int i = (low - 1);                 // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1 && ++comparison; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot && ++comparison)
        {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortExperiment(int arr[], int low, int high, long long &comparison)
{
    if (low < high && ++comparison)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */

        int pi = partitionExperiment(arr, low, high, comparison);

        // Separately sort elements before
        // partition and after partition
        quickSortExperiment(arr, low, pi - 1, comparison);
        quickSortExperiment(arr, pi + 1, high, comparison);
    }
}