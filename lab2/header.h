#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;
int *initRandomArray(int &n);
void writeFile(int comp, int as, string file);
int randomNumber(int n);

void findMajor(int *a, int n);
void findMajorOptimized(int *a, int n);

int gcd(int a, int b);
int gcdRecursive(int a, int b, int &count_comp, int &count_as);

void testGCD(int *arr, int *arr2, int n);
void testGCDRecursive(int *arr, int *arr2, int n);

void wordCloud(string *list, int n);
void wordCloudWorse(string *list, int n);
