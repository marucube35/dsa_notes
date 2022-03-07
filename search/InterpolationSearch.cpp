#include "Header.h"
int interpolationSearch(int* a,int n,int x)
{
    int L = 0, R = n-1;
    while(L<=R) {
        int M = L + (R - L)*((x - a[L])/(a[R] - a[L]));
        if(x==a[M]){
            return M;
        }
        if(x<a[M]){
            R = M - 1;
        }
        else{
            L = M + 1;
        }
    }
    return -1;
}
