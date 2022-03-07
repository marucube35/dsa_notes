#include <iostream>
#include <random>
using  namespace std;
void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}
int* sum(int* a, int * b)
{
    *a = *a + *b;
    return a;
}
void inputArray(int* a, int &n)
{
    for(int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
}
void printArray(int* a, int n)
{
    for(int i = 0; i < n; i++)
    {
        cout<<a[i]<<"  ";
    }cout<<endl;
}
void print2DArray(int** a, int n, int m)
{
    for(int i = 0; i <n; i++)
    {
        printArray(a[i],m);
    }
}
int* findMAx(int* arr, int n)
{
    int max = 0, pos = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            pos = i;
        }
    }
    return &arr[pos];
}
int* findLongestAscendingSubarray(int* a, int n, int &length)
{
    int max = 0, pos;
    for(int i = 0; i < n - 1; i++)
    {
        int count = 1, j = i;
        while(a[j] <= a[j + 1])
        {
            count+=1;
            j++;
        }
        if(count > max)
        {
            max = count;
            pos = i;
        }
    }
    length = max;
    return &a[pos];
}
//!Fix
void swapArrays(int* a, int* b, int &na, int &nb)
{
    // int *c = a;
    // a = b;
    // b = c;
    for(int i = 0; i < nb; i++)
    {
        swap(a[i],b[i]);
    }
}
int* concatenate2Arrays(int* a, int* b, int na, int nb)
{
    int sum = na + nb;
    int* newArr = new int[sum];
    
    if(na > nb)
    {
        int max = na;
        int* bigger = a;
        int* smaller = b;
    }
    int max = nb;
    int* bigger = b;
    int* smaller = a;
    
    for(int i = 0; i < max; i++)
    {
        newArr[i] = bigger[i];
        if(i > sum - max) break;
        newArr[i + max] = smaller[i];
    }
    return newArr;
}
int* merge2Arrays(int* a, int* b, int na, int nb, int &nc)
{
    nc = na + nb;
    int i = 0,j = 0,k = 0;
    int* newArr = new int [nc];

    while(i <= na && j <= nb)
    {
        if(a[i] < b[j]){
            newArr[k++] = a[i++];
        }
        else{
            newArr[k++] = b[j++];
        }
    }
    while(i <= na)
    {
        newArr[k++] = a[i++];
    }
    while(j <= nb)
    {
        newArr[k++] = b[j++];
    }
    return newArr;
}
void initMatrix(int** &A, int length, int width)
{
    A = new int*[length];
    for(int i = 0; i < length; i++)
    {
        A[i] = new int[width];
    }
}
void generateMatrix1(int** A, int &length, int &width)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 100);
    
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j <width; j++)
        {
            auto random_integer =uni(rng);
            A[i][j] = rand() % 10 + 1;
        }
    }
}
int** generateMatrix2(int* a, int* b, int na, int nb)
{
    int** M;
    initMatrix(M, na, nb);
    for(int i = 0; i < na; i++)
    {
        for(int j = 0; j < nb; j++)
        {
            M[i][j] = a[i]*b[j];
        }
    }
    return M;
}
void swapColumns(int** a,int length, int width)
{
    int c1,c2;
    do{
        cout<<"Which columns will be swapped (start at zero) ?"<<endl;
        cout<<"Column 1: "; cin>>c1;
        cout<<"Column 2: "; cin>>c2;
    }while(c1>width || c2>width);

    for(int i = 0; i < length; i++)
    {
        swap(a[i][c1],a[i][c2]);
    }
}
void swapRows(int** a,int length, int width)
{
    int r1,r2;
    do{
        cout<<"Which rows will be swapped (start at zero) ?"<<endl;
        cout<<"Column 1: "; cin>>r1;
        cout<<"Column 2: "; cin>>r2;
    }while(r1>length || r2>length);

    for(int j = 0; j < width; j++)
    {
        swap(a[r1][j],a[r2][j]);
    }
}
int** transposeMatrix(int** a, int length, int width)
{
    int** T;
    initMatrix(T,width*2,length);
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
            T[j][i] = a[i][j];
        }
    }
    return T;
}
int** concatenate2MatricesH(int** a, int** b, int length, int width)
{
    int** M;
    initMatrix(M,length,width*2);
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
            M[i][j] = a[i][j];
            M[i][j+width] = b[i][j];
        }
    }
    return M;
}
int** concatenate2MatricesV(int** a, int** b, int length, int width)
{
    int** M;
    initMatrix(M,length*2,width);
    for(int j = 0; j < width; j++)
    {
        for(int i = 0; i < length; i++)
        {
            M[i][j] = a[i][j];
            M[i+length][j] = b[i][j];
        }
    }
    return M;
}
bool multiple2Matrices(int** a,int** b,int lengtha, int widtha, int lengthb, int widthb)
{
    if(widtha != lengthb) return false;
    int** P;
    initMatrix(P,lengtha,widthb);
    
    for(int k = 0; k < widthb; k++)
    {
        for(int i = 0 ;i < lengtha; i++)
        {
            int sum=0;
            for(int j = 0; j < widtha; j++)
            {
                sum+= a[i][j]*b[j][k];
            }
            cout<<"("<<i<<","<<k<<")"<<sum<<"  ";
            P[i][k] = sum;
        }
    }
    return true;
}
//!Not yet implemented
// int** findSubMatrix(int** a, int length, int width, int &length_, int &width_)
// {
//     do{
//         cout<<"Enter sub matrix size"<<endl;
//         cout<<"Length: ";cin>>length_;
//         cout<<"Width: ";cin>>width_;
//     }while(length_ > length || width_ > width);
// }
int LinearSearch(int* a, int n, int key)
{
    for(int i = 0; i < n; i++)
    {
        if(a[i] == key)
        {
            return i;
        }
    }
    return -1;
}
int SentinelLinearSearch(int* a, int n, int key)
{
    a[n] = key;
    
    int i=0;
    while(1)
    {
        if(a[i++] == key)
            return i;
    }
    if(i==n) 
    {
        return -1;
    }
}
int BinarySearch(int* a, int n, int key)
{
    int left = 0, right = n-1;

    while(left<=right)
    {
        int mid = (left+right)/2;

        if(a[mid] == key)
            return mid;
        if(a[mid] < key)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}
int RecursiveBinarySearch(int* a, int left, int right, int key)
{
    int mid = (left+right)/2;
    if(a[mid] == key)
        return mid;
    if(a[mid] < key)
    {
        return RecursiveBinarySearch(a, mid+1, right, key);
    } 
    else
    {
        return RecursiveBinarySearch(a,left,mid-1,key);
    }
}