#include <iostream>
#include <cmath>
using namespace std;
struct Point{
    float x,y;
};
void initArray(int* &a,int n);
void displayArray(int* a,int n);

int linearSearch(int* a, int n, int x);
int searchMin(float* a,int n);
int searchAllMin(float* a,int* &Mins,int n);

int binarySearch(int* a,int n,int x);
int searchPointQ(Point* a,int n,Point p);
int interpolationSearch(int* a,int n,int x);

