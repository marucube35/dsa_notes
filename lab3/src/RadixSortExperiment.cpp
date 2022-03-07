#include "Sorting.h"

/*
	The radix sorting algorithms - sorting without comparisons with radix 10 and maximum 10 digits number.
	I use the code belong to the book Data Structures and Algorithms in C++ (4th Edition) by Adam Drozdek with my explainations.
	@param data: the input array need to be sorted
	@param n: the length of array
*/
void radixSortExperiment(int *data, int n, long long &comparison)
{
	const int radix = 10;	   // the radix of number
	const int digits = 10;	   // the maximum number of digits
	queue<long> queues[radix]; // create 10 queues (piles/box) to
	/*
		d is the number of loops depend on the maximum number of digits
		factor is the position of digits we consider (1 is the right-most/unit, 10 is the left of right-most/dozen position, etc)
	*/
	for (int d = 1, factor = 1; d <= digits && ++comparison; factor *= radix, d++)
	{
		for (int j = 0; j < n; j++)
			//Push the number in its factor-position appropriate queue/box
			//For example: push 321 in queue labeled "1" if factor-position is 1, so on
			queues[(data[j] / factor) % radix].push(data[j]);
		for (int j = 0, k = 0; j < radix && ++comparison; j++)
		{
			while (!queues[j].empty())
			{
				//Rearrange the order of each element by adding from queue, from 0 to radix
				data[k++] = queues[j].front();
				//After that, remove it from queue
				queues[j].pop();
			}
		}
	}
}
