#include "header.h"

//! Bài làm giả sử các đồ thị sử dụng là đơn đồ thị

NODE *createNODE(int vertex)
{
    NODE *node = new NODE;
    node->vertex = vertex;
    node->adjacent = nullptr;
    return node;
}

void addTail(NODE *&ptr, NODE *node)
{
    if (node == nullptr)
        return;
    if (ptr == nullptr)
    {
        ptr = node;
        return;
    }
    else
    {
        NODE *move = ptr;
        while (move->adjacent != nullptr)
        {
            move = move->adjacent;
        }
        move->adjacent = node;
    }
}

void printList(NODE **list, int n)
{
    cout << "-----Adjacent List-----" << endl;
    for (int i = 0; i < n; i++)
    {
        NODE *move = list[i];
        cout<<i<<" : ";
        while (move != nullptr)
        {
            cout << move->vertex << " ";
            move = move->adjacent;
        }
        cout << endl;
    }
}

void printMatrix(int **a, int n)
{
    cout << "-----Adjacent Matrix-----" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int **readMatrix(string file, int &n)
{
    fstream f(file, ios::in);
    int **matrix = nullptr;

    if (f.is_open())
    {
        string nodes;
        getline(f, nodes);
        n = stoi(nodes);
        matrix = new int *[n];

        for (int i = 0; i < n; i++)
        {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                f >> matrix[i][j];
            }
        }
    }

    f.close();
    return matrix;
}

//Chỉ dành cho đơn đồ thị không có trọng số
NODE **matrixToList(int **a, int n)
{
    NODE **list = new NODE *[n];
    for (int i = 0; i < n; i++)
    {
        list[i] = nullptr;
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == 1)
            {
                addTail(list[i], createNODE(j));
            }
        }
    }
    return list;
}

void parseStringToList(NODE *&node, string row)
{
    if (row.empty())
        return;
    int pos = 0;
    for (int i = 0; i < row.length(); i++)
    {
        int loca = row.find(" ", pos);
        string num;
        if (loca == -1)
        {
            num = row.substr(pos, row.length() - pos);
            i = row.length();
        }
        else
        {
            num = row.substr(pos, loca);
            pos = loca + 1;
        }
        
        try
        {
            addTail(node, createNODE(stoi(num)));
        }
        catch (const std::exception)
        {
            cout << "File's format is not right" << endl;
        }
    }
}

NODE **readAdjacentList(string file, int &n)
{
    //Đọc file và cho vào danh sách kề
    fstream f(file, ios::in);
    if (!f.is_open())
        return nullptr;

    string nodes;
    getline(f, nodes);
    n = stoi(nodes);
    NODE **list = new NODE *[n];
    int i = 0;
    while (!f.eof())
    {
        string row;
        getline(f, row);
        list[i] = nullptr;
        parseStringToList(list[i++], row);
    }
    f.close();
    return list;
}

int **listToMatrix(NODE **list, int n)
{
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n]{0};
        NODE *move = list[i];
        for (int j = 0; j < n; j++)
        {
            if (move != nullptr)
            {
                matrix[i][move->vertex] = 1;
                move = move->adjacent;
            }
        }
    }
    return matrix;
}