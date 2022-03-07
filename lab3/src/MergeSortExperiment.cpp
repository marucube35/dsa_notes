#include "Sorting.h"

void mergeExperiment(int *a, int left, int mid, int right, long long &count_compare)
{
    int *temp = new int[right - left + 1];

    int k = 0;
    int i = left;
    int j = mid + 1;

    while ((++count_compare && i <= mid) && (++count_compare && j <= right))
    {
        if (++count_compare && a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (++count_compare && i <= mid)
    {
        temp[k++] = a[i++];
    }
    while (++count_compare && j <= right)
    {
        temp[k++] = a[j++];
    }

    for (int i = left; ++count_compare && i <= right; i++)
    {
        a[i] = temp[i - left];
    }
}

void mergeSortExperiment(int *a, int left, int right, long long &count_compare)
{
    if (++count_compare && left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergeSortExperiment(a, left, mid, count_compare);
    mergeSortExperiment(a, mid + 1, right, count_compare);
    mergeExperiment(a, left, mid, right, count_compare);
}
