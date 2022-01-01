#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
using namespace std;

void writeFile(int comp, int as, string file)
{
    fstream f(file, ios::app);
    f << comp << "," << as << endl;
    f.close();
}

string *readWords(string file)
{
    string *str_arr = new string[100];
    fstream f(file, ios::in);
    int i = 0;

    while (!f.eof() && i < 100)
    {
        string word;
        f >> word;
        str_arr[i++] = word;
    }

    f.close();
    return str_arr;
}

int randomNumber(int n)
{
    return rand() % (n - 1 + 1) + 1;
}

int *initRandomArray(int &n)
{
    cout << "How many elements?" << endl;
    cin >> n;
    cout << "Size of element?" << endl;
    int size;
    cin >> size;
    int *arr = new int[n];

    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        arr[i] = randomNumber(size);
    }
    return arr;
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Bài 1
void findMajor(int *a, int n)
{
    int count_comp = 0;
    int count_as = 0;

    ++count_as;
    for (int i = 0; ++count_comp && i < n; i++)
    {
        int count = 1;
        count_as += 2;

        for (int j = i + 1; ++count_comp && j < n; j++)
        {
            if (++count_comp && a[i] == a[j])
            {
                count++;
                ++count_as;
            }
        }

        //*Nếu số k nào đó xuất hiện hơn một nửa, thì nó xuất hiện nhiều nhất
        //*Vì vậy mà ta không cần dùng biến max
        if (++count_comp && count > n / 2)
        {
            cout << a[i] << endl;
            cout << "--------" << endl;
            return;
        }

        cout << count_comp << "\t" << count_as << endl;
        writeFile(count_comp,count_as,"major1.csv");
    }
    cout << "NO" << endl;
    cout << "--------" << endl;
}

//?Tham khảo Geeksforgeeks: https://www.geeksforgeeks.org/majority-element/
//?Nội dung tham khảo: tìm phần tử majority có tần suất lớn hơn n/2.
//?Nội dung liên quan: kiểu dữ liệu map (dictionaries), vòng lặp for each và kiểu dữ liệu auto.

void findMajorOptimized(int *a, int n)
{
    //*Một map bản chất là một mảng,
    //*nhưng trị số index của nó có thể không phải là kiểu int tuần tự.

    //?Duyệt qua mảng để thiết lập map
    map<int, int> freq_table;

    int count_comp = 0;
    int count_as = 0;

    ++count_as;
    for (int i = 0; ++count_comp && i < n; i++)
    {
        freq_table[a[i]]++;
        ++count_as;
    }

    //?Duyệt qua tìm phần tử có tần suất xuất hiện lớn hơn n/2
    ++count_as;
    for (auto item : freq_table)
    {
        ++count_comp;
        if (++count_comp && item.second > n / 2)
        {
            cout << item.first << endl;
            cout << "-------" << endl;
            return;
        }

        cout << count_comp << "\t" << count_as << endl;
        writeFile(count_comp,count_as,"major2.csv");
    }

    cout << "NO" << endl;
    cout << "-------" << endl;
}

//Bài 2
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

//Bài 3
void wordCloud(string *list, int n)
{
    int count_comp = 0;
    int count_as = 0;
    map<string, int> cloud;

    for (int i = 0; ++count_comp && i < n; i++)
    {
        ++count_as;
        cloud[list[i]]++;
    }

    for (auto word : cloud)
    {
        ++count_comp;
        cout << word.first << ": " << word.second << endl;

        cout << count_comp << "\t" << count_as << endl;
        writeFile(count_comp, count_as, "wordcloud2.csv");
    }
}

bool compStr(string a, string b)
{
    if (a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void merge(string *a, int left, int mid, int right)
{
    string *temp = new string[right - left + 1];
    //*Mảng thứ nhất từ left đến mid, mảng thứ hai từ mid+1 đến right
    int k = 0;
    int i = left;
    int j = mid + 1;
    //?Khi hai mảng con chưa xét đến phần tử cuối
    while (i <= mid && j <= right)
    {
        //?So sánh phần tử đầu mỗi mảng và cho vào mảng phụ
        if (compStr(a[i], a[j]))
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
        //?Chép các phần tử còn lại (nếu còn)
        while (i <= mid)
        {
            temp[k++] = a[i++];
        }
        while (j <= right)
        {
            temp[k++] = a[j++];
        }
        //?Chép mảng phụ lại vào mảng chính
        for (int i = 0; i < k - 1; i++)
        {
            //*Index của a tính từ left
            a[left + i] = temp[i];
        }
    }
}
void mergeSort(string *a, int left, int right)
{
    if (left >= right)
        return;
    //*Tìm vị trí giữa mảng để chia
    int mid = (left + right) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

void wordCloudWorse(string *list, int n)
{
    int count_comp = 0;
    int count_as = 0;

    mergeSort(list, 0, n - 1);

    string curr = list[0];
    int count = 1;
    count_as += 2;

    for (int i = 1; ++count_comp && i < n; i++)
    {
        if (++ count_comp && list[i] != curr)
        {
            //Xuất ra từ trước đó và tần số của nó
            cout << curr << ": ";
            cout << count << endl;
            //Reset stack
            count = 1;
            curr = list[i];
            count_as += 2;
        }
        else
        {
            count++;
            ++count_as;
        }

        cout << count_comp << "\t" << count_as << endl;
        writeFile(count_comp, count_as, "wordcloud1.csv");
    }
}

int main()
{
    //Bài 1
    // int n;
    // int *arr = initRandomArray(n);

    // findMajor(arr,n);
    // findMajorOptimized(arr, n);

    //Bài 2
    // int n;
    // int *arr = initRandomArray(n);
    // int *arr2 = initRandomArray(n);

    // testGCD(arr,arr2,n);
    // testGCDRecursive(arr,arr2,n);

    //Bài 3
    // string *list = readWords("words.txt");
    // wordCloud(list, 100);
    // wordCloudWorse(list,100);

    system("pause");
}
