#include "Header.h"

int linearSearch(int* a, int n, int x)
{
    for(int i=0;i<n;i++){
        if(a[i]==x){
            return i;
        }
    }
    return -1;
}
int searchMin(float* a,int n)
{
    int min=a[0];
    int index=0;
    for(int i=0;i<n;i++){
        if(a[i]<min){
            min=a[i];
            index=i;
        }
    }
    return index;
}
int searchAllMin(float* a,int* &Mins,int n)
{
    float min=a[0];
    Mins = new int[n];
    for(int i=0;i<n;i++){
        if(a[i]<min){
            min=a[i];
        }
    }
    cout<<min<<endl;
    int count=0;
    for(int i=0;i<n;i++)
    {
        if(a[i]==min){
            Mins[count++]=i;
        }
    }
    return count;
}
void displayArray(int* a,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<< "  ";
    }cout<<endl;
}