#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE
{
    string ID;
    float weight;
    int product;
    NODE *pNext;
};

struct LIST
{
    NODE *pHead;
    NODE *pTail;
};

NODE *createNode(NODE info)
{
    NODE *node = new NODE;
    node->ID = info.ID;
    node->weight = info.weight;
    node->product = info.product;
    node->pNext = nullptr;
    return node;
}

LIST initList()
{
    LIST list;
    list.pHead = list.pTail = nullptr;
    return list;
}

int animal(string line);

void printNode(NODE info)
{
    cout << info.ID << " " << info.weight << " " << info.product << endl;
}
void printList(LIST list)
{
    NODE *move = list.pHead;
    while (move != NULL)
    {
        printNode(*move);
        move = move->pNext;
    }
    cout << endl;
}
void printListType(LIST list)
{
    NODE *move = list.pHead;
    NODE *move2 = list.pHead;
    cout << "Ga dat chuan" << endl;
    while (move != NULL)
    {
        if (animal(move->ID) == 1)
        {
            printNode(*move);
        }
        move = move->pNext;
    }
    cout << "Vit dat chuan" << endl;
    while (move2 != NULL)
    {
        if (animal(move2->ID) == 2)
        {
            printNode(*move2);
        }
        move2 = move2->pNext;
    }

    cout << endl;
}

void addHead(LIST &list, NODE *node)
{
    if (list.pHead == nullptr)
    {
        list.pHead = list.pTail = node;
    }
    else
    {
        node->pNext = list.pHead;
        list.pHead = node;
    }
}

void addTail(LIST &list, NODE *node)
{
    if (list.pHead == nullptr)
    {
        list.pHead = list.pTail = node;
    }
    else
    {
        list.pTail->pNext = node;
        list.pTail = node;
    }
}

int animal(string line)
{
    string type = line.substr(0, 4);
    if (type == "chic") //1 là gà
        return 1;
    else if (type == "duck") //2 là vịt
        return 2;
    else
        return 0;
}

bool isStandard(NODE info)
{
    if (animal(info.ID) != 0)
    {
        //Gà
        if (animal(info.ID) == 1)
        {
            if (info.product <= 32 && info.product >= 25)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        //vịt
        else
        {
            if (info.product <= 22 && info.product >= 15)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void classify(LIST &list)
{
    if (isStandard(*list.pHead) == false)
    {
        list.pHead = list.pHead->pNext;
    }
    NODE *move = list.pHead;
    while (move->pNext->pNext != NULL)
    {
        if (isStandard(*(move->pNext)) == false)
        {
            move->pNext = move->pNext->pNext;
        }
        else
        {
            move = move->pNext;
        }
    }
    if (isStandard(*(move->pNext)) == false)
    {
        move->pNext = nullptr;
        list.pTail = move;
    }
}

NODE stringToNode(string line)
{
    NODE info;
    int pos = line.find_first_of(" ", 0);
    info.ID = line.substr(0, pos);
    int pos2 = line.find_first_of(" ", pos + 1);
    info.weight = stof(line.substr(pos + 1, pos2));
    info.product = stoi(line.substr(pos2 + 1, line.length()));
    info.pNext = nullptr;
    return info;
}

void readFile(LIST &list)
{
    list = initList();

    fstream f("data.txt", ios::in);
    if (!f.is_open())
        return;

    while (!f.eof())
    {
        string line;
        getline(f, line);
        if (animal(line) != 0)
        {
            NODE *node = createNode(stringToNode(line));
            if (animal(line) == 1)
            {
                addHead(list, node);
            }
            else
            {
                addTail(list, node);
            }
        }
    }
    f.close();
}

void SoS(int k, int sum, int total, int w[], int n, bool s[], int t,int &comp,int &assign)
{
    if (++comp && sum == t)
    {
        for (int i = 0; ++comp && i < n; i++)
            if (++comp && s[i] == true)
                cout << w[i] << " ";
        cout << endl;
    }
    else
    {
        if ((++comp && t <= sum + total) && (++comp && t >= sum + w[k]))
        {
            
            s[k] = true;++assign;
            SoS(k + 1, sum + w[k], total - w[k], w, n, s, t,comp,assign);
            s[k] = false;++assign;
            SoS(k + 1, sum, total - w[k], w, n, s, t,comp,assign);
        }
    }
}


void Bai01()
{
    LIST list;
    readFile(list);
    printList(list);
    classify(list);
    printListType(list);
}

void Bai02()
{
    int comp = 0,assign =0;
    // Gia tri vi du, sinh vien co the thay doi de kiem tra
    int w[100] = {3, 5, 6, 7};
    int n = 4;  // So luong so nguyen duong
    int t = 15; // Tong t can tim tap con
    // Bat dau thuat toan
    bool s[100] = {false};
    int total = 0;
    for (int i = 0; i < n; i++)
        total += w[i];
    if (w[0] <= t && t <= total)
        SoS(0, 0, total, w, n, s, t,comp, assign);
    // Ket thuc thuat toan
    // In ra so phep gan, so phep so sanh
    cout<<assign<<" "<<comp<<endl;
}

int main(int argc, char **argv)
{
    Bai01();
    // Bai02();

    system("pause");
    return 0;
}