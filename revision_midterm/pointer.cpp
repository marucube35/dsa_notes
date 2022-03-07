#include <iostream>
#include <string.h>
#define MAX_SIZE 1000000
using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int add(int *a, int *b)
{
    return *a + *b;
}

int sumArr(int *a, int n)
{
    int sum = 0;
    n -= 1;
    while (n >= 0)
    {
        sum += a[n--];
    }
    return sum;
}

int length(char *str)
{
    int len = 0;
    while (*str != '\0')
    {
        len += 1;
        str += 1;
    }
    return len;
}

void copyStr(char *src, char *dst)
{
    int lenSrc = length(src);
    for (int i = 0; i < lenSrc; i++)
    {
        dst[i] = src[i];
    }
}

char *concenateStr(char *str1, char *str2)
{
    int lenStr1 = length(str1);
    int lenStr2 = length(str2);
    char *result = new char[lenStr1 + lenStr2 + 1];

    for (int i = 0; i < lenStr1; i++)
    {
        result[i] = str1[i];
    }

    for (int i = 0; i < lenStr2; i++)
    {
        result[i + lenStr1] = str2[i];
    }
    return result;
}

void inputStr(char *&str)
{
    cout << "Enter string: " << endl;
    char *temp = new char[MAX_SIZE];
    cin.get(temp, MAX_SIZE, '\n');
    cin.ignore(MAX_SIZE, '\n');
    str = new char[strlen(temp) + 1];
    strcpy(str, temp);
}

void printReverseArray(int *a, int n)
{
    if (n > 0)
    {
        cout << a[n - 1] << " ";
        printReverseArray(a, n - 1);
    }
}

int main(int argc, char **argv)
{
    int a = 5, b = 6;
    int *ptrA = &a, *ptrB = &b;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printReverseArray(arr, 10);

    system("pause");
    return 0;
}