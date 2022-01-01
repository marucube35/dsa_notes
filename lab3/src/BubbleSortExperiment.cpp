#include "Sorting.h"

//Exchange the value of two variables
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
//Experient purpose function of bubble sort
void bubbleSortExperiment(int a[], int n, long long &count_cmp)
{
    for (int i = 0; ++count_cmp && i < n - 1; i++)
    {
        for (int j = 0; ++count_cmp && j < n - i - 1; j++)
        {
            if (++count_cmp && a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}
