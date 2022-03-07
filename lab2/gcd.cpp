#include "header.h"

int gcd(int a, int b)
{
    int count_comp = 0;
    int count_as = 0;

    while (++count_comp && a * b != 0)
    {
        if (++count_comp && a > b)
        {
            a = a % b;
            ++count_as;
        }
        else
        {
            b = b % a;
            ++count_as;
        }
    }

    cout << count_comp << "\t" << count_as << endl;
    writeFile(count_comp, count_as, "gcd1.csv");

    return a + b;
}

int gcdRecursive(int a, int b, int &count_comp, int &count_as)
{
    if (++count_comp && b == 0)
        return a;
    return gcdRecursive(b, a % b, count_comp, count_as += 2);
}

void testGCD(int *arr, int *arr2, int n)
{

    for (int i = 0; i < n; i++)
    {
        gcd(arr[i], arr2[i]);
    }
}
void testGCDRecursive(int* arr, int* arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        int count_comp = 0;
        int count_as = 0;

        gcdRecursive(arr[i], arr2[i], count_comp, count_as);

        cout << count_comp << "\t" << count_as << endl;
        writeFile(count_comp, count_as, "gcd2.csv");
    }
}