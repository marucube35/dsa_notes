#include "Header.h"
int binarySearch(int* a,int n,int x)
{
    int L=0,R=n-1;
    while(L<=R)
    {
        int M = (L+R)/2;
        if(x == a[M])
            return M;
        if(x > a[M]){
            R = M - 1;
        }
        else{
            L = M + 1;
        }
    }
    return -1;
}
float calcDistance(Point a, Point b)
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
int searchPointQ(Point* a,int n,Point p)
{
    float min = calcDistance(p,a[0]);
    int index;
    for(int i=0;i<n;i++){
        float distance = calcDistance(p,a[i]);
        if(distance < min)
        {
            min = distance;
            index = i;
        }
    }
    return index;
}