#include "header.h"

void printMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int **readMatrix(string file, int &n)
{
    ifstream f(file);
    if (f.is_open())
    {
        f >> n;
        int **matrix = new int *[n]
        { 0 };

        for (int i = 0; i < n; i++)
        {
            matrix[i] = new int[n]{0};
            for (int j = 0; j < n; j++)
            {
                f >> matrix[i][j];
            }
        }

        return matrix;
    }
    return nullptr;
}

VERTEX *createVertex(int value)
{
    VERTEX *node = new VERTEX;
    node->key = value;
    node->adjacent = nullptr;
    return node;
}

void addTail(VERTEX *&node, int value)
{
    VERTEX *newNode = createVertex(value);
    if (node == nullptr)
        node = newNode;
    else
    {
        VERTEX *move = node;
        while (move->adjacent != nullptr)
        {
            move = move->adjacent;
        }
        move->adjacent = newNode;
    }
}

void printList(VERTEX **list, int n)
{
    for (int i = 0; i < n; i++)
    {
        VERTEX *move = list[i];
        cout << i << " : ";
        while (move != nullptr)
        {
            cout << move->key << "  ";
            move = move->adjacent;
        }
        cout << endl;
    }
}

void parseStringToList(string line, VERTEX *list)
{

    int pos = 0, deli = 0;
    while (deli != string::npos)
    {
        deli = line.find_first_of(" ", pos);
        string num = line.substr(pos, deli - pos);
        cout << num << " ";
        pos = deli + 1;
    }
    cout << endl;
}

VERTEX **readList(string file, int &n)
{
    ifstream f(file);
    if (f.is_open())
    {
        string line;
        getline(f, line);
        VERTEX **list = new VERTEX *[stoi(line)]
        { 0 };

        int i = 0;
        while (!f.eof())
        {
            getline(f, line);
            if (line == "")
                continue;
            parseStringToList(line, list[i++]);
        }
    }
    return nullptr;
}
