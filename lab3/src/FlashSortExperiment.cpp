#include "Sorting.h"

void flashSortExperiment(int a[], int n, long long &count_compare)
{
    int m = int(0.45 * n);
    int *l = new int[m];
    for (int i = 0; ++count_compare && i < m; i++)
    {
        l[i] = 0;
    }

    int max = 0;
    int minVal = a[0];
    for (int i = 1; ++count_compare && i < n; i++)
    {
        if (++count_compare && a[i] < minVal)
            minVal = a[i];
        if (++count_compare && a[i] > a[max])
            max = i;
    }
    if (++count_compare && a[max] == minVal)
        return;

    double c1 = (double)(m - 1) / (a[max] - minVal);
    for (int i = 0; ++count_compare && i < n; i++)
    {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }

    for (int i = 1; ++count_compare && i < m; i++)
    {
        l[i] += l[i - 1];
    }

    swap(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (++count_compare && nmove < n - 1)
    {
        while (++count_compare && j > l[k] - 1)
        {
            j++;
            k = int(c1 * (a[j] - minVal));
        }
        flash = a[j];
        if (++count_compare && k < 0)
            break;
        while (++count_compare && j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    delete[] l;

    insertionSortExperiment(a, n,count_compare);
}
