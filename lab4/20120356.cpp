#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
int p = 31;
int m = 1000000009;
int size = 2000;
using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

void printCompany(Company info)
{
    cout << "Name: " << info.name << endl;
    cout << "Profit: " << info.profit_tax << endl;
    cout << "Address: " << info.address << endl;
}

void printCompanyList(vector<Company> list_company)
{
    for (int i = 0; i < list_company.size(); i++)
    {
        printCompany(list_company[i]);
    }
}

void printHashTable(Company *hash_table)
{
    for (int i = 0; i < 2000; i++)
    {
        cout << "a[" << i << "]: ";
        if (hash_table[i].name == "")
            cout << "NULL" << endl;
        else
            cout << hash_table[i].name << endl;
    }
}

Company parseString(string info)
{
    Company company;
    int pos1 = 0;
    int pos2 = info.find_first_of("|", pos1);
    company.name = info.substr(pos1, pos2 - pos1);
    pos1 = pos2 + 1;
    pos2 = info.find_first_of("|", pos1);
    company.profit_tax = info.substr(pos1, pos2 - pos1);
    company.address = info.substr(pos2 + 1, info.length() - pos2 - 1);
    return company;
}

vector<Company> ReadCompanyList(string file_name)
{
    vector<Company> list;
    fstream f(file_name, ios::in);

    if (f.is_open())
    {
        string line;
        getline(f, line);
        while (!f.eof())
        {
            string line;
            getline(f, line);
            if (line != "")
                list.push_back(parseString(line));
        }
    }
    else
    {
        cout << "Find not found!";
    }
    f.close();
    return list;
}

long long power(int x, int y)
{
    long long result = 1;
    while (y != 0)
    {
        result = ((result % m) * (x % m)) % m;
        --y;
    }
    return result;
}

long long HashString(string company_name)
{
    string s;
    int str_size = company_name.length();
    if (str_size <= 20)
        s = company_name;
    else
        s = company_name.substr(str_size - 20, 20);

    long long hash = 0;

    for (int i = 0; i < s.length(); i++)
    {
        char ch = s.at(i);
        int ascii = int(ch);

        hash = hash + ((ascii % m) * (power(p, i) % m)) % m;
    }
    hash = hash % m;
    return hash;
}

void linearProbing(Company *hash_table, long long &hash)
{
    if (hash >= size)
        hash = hash % size;

    //Tìm tuyến tính đến khi nào có chỗ trống
    int count = 1;
    while (hash_table[hash].name != "")
    {
        hash = ((hash % size) + 1) % size;

        count += 1;
        if (count > 2001)
        {
            cout << "Hash Table is full" << endl;
            hash = -1;
            break;
        }
    }
}

Company *CreateHashTable(vector<Company> list_company)
{
    Company *hash_table = new Company[size];

    for (int i = 0; i < list_company.size(); i++)
    {
        long long hash = HashString(list_company[i].name);
        linearProbing(hash_table, hash);

        if (hash != -1)
            hash_table[hash] = list_company[i];
        else
            return hash_table;
    }

    return hash_table;
}

bool checkHashTable(Company *hash_table, int real_size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (hash_table[i].name != "")
            count += 1;
    }
    if (count == real_size)
        return true;
    return false;
}

void inputCompany(Company &company)
{
    cout << "Name? ";
    getline(cin, company.name);
    cout << "Profit_tax? ";
    getline(cin, company.profit_tax);
    cout << "Address? ";
    getline(cin, company.address);
}

void Insert(Company *hash_table, Company company)
{
    long long hash = HashString(company.name);
    linearProbing(hash_table, hash);
    hash_table[hash] = company;
    cout << "Was added to " << hash << endl;
}

Company *Search(Company *hash_table, string company_name)
{
    long long hash = HashString(company_name);

    if (hash >= size)
        hash = hash % size;

    int count = 1;
    while (count < 2001)
    {
        if (hash_table[hash].name != "")
        {
            if (hash_table[hash].name == company_name)
            {
                cout << "Index: " << hash << endl;
                Company *result = &hash_table[hash];
                return result;
            }
        }

        hash = ((hash % size) + 1) % size;
        count += 1;
    }

    cout << "Company cannot be found" << endl;
    return nullptr;
}

int main()
{
    vector<Company> list = ReadCompanyList("MST.txt");
    Company *hash_table = CreateHashTable(list);

    // printHashTable(hash_table);
    // cout<<checkHashTable(hash_table,list.size())<<endl;

    cout << "Search for:" << endl;
    string comName;
    getline(cin, comName);
    cout << Search(hash_table, comName) << endl;

    system("pause");
    return 0;
}
