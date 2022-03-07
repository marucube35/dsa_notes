#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <time.h>
#include <queue>
using namespace std;
using namespace std::chrono;

void swap(int& a, int& b);
//Bubble Sort
void bubbleSortExperiment(int a[], int n, long long& count_cmp);
//Counting Sort
int maximumValue(int* data, int size);
void setValueNIL(int*& arr, int size);
int maximumValueExperiment(int* data, int size, long long& comparison);
void setValueNILExperiment(int*& arr, int size, long long& comparison);
int* countingSortExperiment(int* data, int size, long long& comparison);
//Flash Sort
void flashSortExperiment(int a[], int n, long long& count_compare);
//Heap Sort
void heapifyExperiment(int* arr, int n, int i, long long& count_compare);
void heapSortExperiment(int* arr, int n, long long& count_compare);
//Insertion Sort
void insertionSortExperiment(int a[], int n, long long& count_cmp);
//Merge Sort
void mergeExperiment(int* a, int left, int mid, int right, long long& count_compare);
void mergeSortExperiment(int* a, int left, int right, long long& count_compare);
//Radix Sort
void radixSortExperiment(int* data, int n, long long& comparison);
//Selection Sort
void selectionSortExperiment(int arr[], int n, long long& comparison);
//Shaker Sort
void shakerSortExperiment(int a[], int n, long long& count_cmp);
//Shell Sort
void insertionSortExtendedExperiment(int* data, int n, int gap, long long& comparison);
void shellSortExperiment(int* data, int n, long long& comparison);
//Quick Sort
int partitionExperiment(int arr[], int low, int high, long long& comparison);
void quickSortExperiment(int arr[], int low, int high, long long& comparison);