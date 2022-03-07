#include "header.h"

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