#include <iostream>
using namespace std;

void printFirst50N(int n)
{
    if (n > 0)
    {
        cout << 51 - n << endl;
        printFirst50N(n - 1);
    }
}

int sum(int n)
{
    if (n > 0)
    {
        return n + sum(n - 1);
    }
}

int main(int argc, char **argv)
{
    system("pause");
    return 0;
}