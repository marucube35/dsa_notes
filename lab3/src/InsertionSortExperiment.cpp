#include "Sorting.h"

void insertionSortExperiment(int a[], int n, long long &count_cmp)
{
     for (int i = 1; ++count_cmp && i < n; i++)
     {
          int key = a[i];
          int j = i - 1;
          while ((++count_cmp && j >= 0) && (++count_cmp && key < a[j]))
          {
               a[j + 1] = a[j];
               j--;
          }
          a[j + 1] = key;
     }
}
