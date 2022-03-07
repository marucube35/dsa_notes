#include "Sorting.h"

void insertionSortExtendedExperiment(int *data, int n, int gap, long long &comparison)
{
	for (int i = gap; i < n && ++comparison; i += gap)
	{
		for (int j = i; j >= gap && ++comparison; j -= gap)
		{
			if (data[j] < data[j - gap] && ++comparison)
			{
				swap(data[j], data[j - gap]);
			}
		}
	}
}

void shellSortExperiment(int *data, int n, long long &comparison)
{
	for (int h = n / 2; h > 2 && ++comparison; h /= 2)
	{ //h is the gap
		for (int j = 0; j < h && ++comparison; j++)
		{ //sort each sublist
			insertionSortExtendedExperiment(data, n - j, h, comparison);
		}
	}
	insertionSortExtendedExperiment(data, n, 1, comparison);
}