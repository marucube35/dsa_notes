#include "header.h"

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
