#include "Sorting.h"

//Find the maximun value in array by traversal and compare
int maximumValueExperiment(int *data, int size, long long &comparison)
{
	long max = data[0];
	for (int i = 0; i < size && ++comparison; i++)
	{
		if (max < data[i] && ++comparison)
			max = data[i];
	}
	return max;
}
//Set all the element in an array is 0
void setValueNILExperiment(int *&arr, int size, long long &comparison)
{
	for (int i = 0; i < size && ++comparison; i++)
	{
		arr[i] = 0;
	}
}

//Counting Sort implement
int *countingSortExperiment(int *data, int size, long long &comparison)
{
	//find the maximum value in array
	int max = maximumValueExperiment(data, size, comparison);
	//create array to add the number to its position in sorting
	int *result = new int[size];
	//create array of number in close range [0, max]
	int *temp = new int[max + 1];
	//set all of them 0
	setValueNILExperiment(temp, max + 1, comparison);
	//count the frequency of element in input array
	for (int i = 0; i < size && ++comparison; i++)
	{
		temp[data[i]]++;
	}
	//count the number in array which is smaller or equal each element in array
	for (int i = 1; i < max + 1 && ++comparison; i++)
	{
		temp[i] += temp[i - 1];
	}
	//place each element to apropriate position in result array
	for (int i = 0; i < size && ++comparison; i++)
	{
		result[temp[data[i]] - 1] = data[i];
		temp[data[i]]--;
	}
	return result;
}
