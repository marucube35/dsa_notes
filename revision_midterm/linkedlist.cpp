#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node *next;
};

struct List
{
    Node *head;
    Node *tail;
};

void printList(List *L)
{
    Node *move = L->head;
    while (move != nullptr)
    {
        cout << move->key << "->";
        move = move->next;
    }
    cout << endl;
}

Node *createNode(int data)
{
    Node *node = new Node;
    node->key = data;
    node->next = NULL;
    return node;
}

List *createList(Node *node)
{
    List *list = new List;
    list->head = list->tail = node;
    return list;
}

bool addHead(List *&L, int data)
{
    Node *node = createNode(data);
    if (node == NULL)
        return false;

    if (L->head == NULL)
    {
        L->head = L->tail = node;
        return true;
    }
    else
    {
        node->next = L->head;
        L->head = node;
        return true;
    }
}

bool addTail(List *&L, int data)
{
    Node *node = createNode(data);
    if (node == NULL)
        return false;

    if (L->head == NULL)
    {
        L->head = L->tail = node;
        return true;
    }
    else
    {
        L->tail->next = node;
        L->tail = node;
        return true;
    }
}

void removeHead(List *&L)
{
    if (L == NULL || L->head == NULL)
        return;
    Node* move = L->head;
    L->head = move->next;
}

void removeTail(List *&L)
{
    if (L == NULL || L->head == NULL)
        return;
    Node *move = L->head;
    while (move->next->next != nullptr)
    {
        move = move->next;
    }
    Node *temp = move->next;
    move->next = nullptr;
    L->tail = move;
    delete temp;
}

void removeAll(List *&L)
{
    Node *temp = L->head;
    L->head = nullptr;
    delete temp;
}

void removeBefore(List *&L, int val)
{
    Node *move = L->head;
    while (move->next->next != nullptr)
    {
        if (move->next->next->key == val)
        {
            move->next = move->next->next;
        }
        else
        {
            move = move->next;
        }
    }
}

void removeAfter(List *&L, int val)
{
    Node *move = L->head;
    while (move->next != nullptr)
    {
        if (move->key == val)
        {
            move->next = move->next->next;
        }
        move = move->next;
    }
}

bool addPos(List *&L, int data, int pos)
{
    //Vị trí đầu
    if (pos == 1)
    {
        return addHead(L, data);
    }

    //Vị trí giữa
    Node *move = L->head;
    int count = 1;
    while (move != nullptr)
    {
        if (pos == count + 1)
        {
            Node *node = createNode(data);
            if (node == nullptr)
                return false;
            node->next = move->next;
            move->next = node;
        }
        move = move->next;
        count += 1;
    }

    //Vị trí cuối
    if (pos == count)
    {
        return addTail(L, data);
    }
}

void removePos(List *&L, int pos)
{
    //Xóa 1
    if (pos == 1)
    {
        removeHead(L);
        return;
    }

    //Xóa từ 2 đến n
    Node *move = L->head;
    int count = 1;
    while (move->next != nullptr)
    {
        if (pos == count + 1)
        {
            Node *temp = move->next;
            move->next = move->next->next;
            delete temp;
        }
        else
        {
            move = move->next;
        }
        count += 1;
    }
}

bool addBefore(List *&L, int data, int val)
{
    if (L->head->key == val)
    {
        return addHead(L, data);
    }

    Node *move = L->head;
    while (move->next != nullptr)
    {
        if (move->next->key == val)
        {
            Node *node = createNode(data);
            if (node == nullptr)
                return false;
            node->next = move->next;
            move->next = node;
            return true;
        }
        move = move->next;
    }
}

bool addAfter(List *&L, int data, int val)
{
    Node *move = L->head;
    while (move->next != nullptr)
    {
        if (move->key == val)
        {
            Node *node = createNode(data);
            if (node == nullptr)
                return false;
            node->next = move->next;
            move->next = node;
            return true;
        }
        move = move->next;
    }

    if (move->key == val)
    {
        return addTail(L, data);
    }
}

int countElements(List *L)
{
    Node *move = L->head;
    int count = 0;
    while (move != nullptr)
    {
        count += 1;
        move = move->next;
    }
    return count;
}

List *reverseList(List *L)
{
    Node *curr = L->head;
    Node *prev = nullptr, *next = nullptr;
    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->tail = L->head;
    L->head = prev;
}

void removeDuplicate(List *&L)
{
    Node *move1 = L->head;

    while (move1->next != nullptr)
    {
        Node *move2 = move1;
        while (move2->next->next != nullptr)
        {
            if (move2->next->key == move1->key)
            {
                Node *temp = move2->next;
                move2->next = move2->next->next;
                delete temp;
            }
            move2 = move2->next;
        }
        //Xử lý xóa cuối
        if(move2->next->key == move1->key)
        {
            removeTail(L);
        }
        move1 = move1->next;
    }
}

void removeElement(List *&L, int key)
{
    //Xử lý xóa đầu
    while (L->head->key == key)
    {
        removeHead(L);
    }
    Node *move = L->head;
    while(move->next->next != nullptr)
    {
        if(move->next->key == key)
        {
            Node*temp = move->next;
            move->next = move->next->next;
            delete temp;
        }
        move = move->next;
    }
    //Xử lý xóa cuối
    if(move->next->key == key)
    {
        removeTail(L);
    }
}

int main(int argc, char **argv)
{
    Node *first = createNode(10);
    List *l = createList(first);
    addTail(l, 10);
    addTail(l, 15);
    addTail(l, 13);
    addTail(l, 14);
    addPos(l, 14, 2);
    addAfter(l, 17, 12);
    printList(l);
    removeDuplicate(l);
    printList(l);
    system("pause");
    return 0;
}