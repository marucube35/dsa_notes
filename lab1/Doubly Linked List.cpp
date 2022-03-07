#include "Doubly Linked List.h"
void printDoubleList(d_List list)
{
    if (list.pHead != nullptr)
    {
        d_NODE *move = list.pHead;
        while (move != nullptr)
        {
            cout << move->key << "  ";
            move = move->pNext;
        }
        cout << endl;
    }
}
void printReverseDoubleList(d_List list)
{
    if (list.pTail != nullptr)
    {
        d_NODE *move = list.pTail;
        while (move != nullptr)
        {
            cout << move->key << "  ";
            move = move->pPrev;
        }
        cout << endl;
    }
}
d_NODE *createDoubleNode(int data)
{
    d_NODE *node = new d_NODE;
    node->key = data;
    node->pNext = node->pPrev = nullptr;
    return node;
}
d_List createDoubleList(d_NODE *node)
{
    d_List list;
    list.pHead = list.pTail = node;
    return list;
}
bool addHead(d_List &list, int data)
{
    d_NODE *node = createDoubleNode(data);
    if (node == nullptr)
        return false;
    if (list.pHead == nullptr)
    {
        list.pHead = list.pTail = node;
    }
    else
    {
        node->pNext = list.pHead;
        list.pHead->pPrev = node;
        list.pHead = node;
    }
    return true;
}
bool addTail(d_List &list, int data)
{
    d_NODE *node = createDoubleNode(data);
    if (node == nullptr)
        return false;

    if (list.pHead == nullptr)
    {
        list.pHead = list.pTail = node;
    }
    else
    {
        node->pPrev = list.pTail;
        list.pTail->pNext = node;
        list.pTail = node;
    }
    return true;
}
void removeHead(d_List &list)
{
    d_NODE *temp = list.pHead;
    if (list.pHead != nullptr && list.pHead->pNext != nullptr)
    {
        list.pHead = list.pHead->pNext;
        list.pHead->pPrev = nullptr;
        delete temp;
    }
    else
    {
        list.pHead = nullptr;
        delete temp;
    }
}
void removeTail(d_List &list)
{
    d_NODE *temp = list.pTail;
    if (list.pHead != nullptr && list.pHead->pNext != nullptr)
    {
        list.pTail = list.pTail->pPrev;
        list.pTail->pNext = nullptr;
        delete temp;
    }
    else
    {
        list.pHead = nullptr;
        delete temp;
    }
}
void removeAll(d_List &list)
{
    delete list.pHead;
    delete list.pTail;
    list.pHead = list.pTail = nullptr;
}
void removeBefore(d_List &list, int val)
{
    d_NODE *move = list.pHead;
    d_NODE *temp;

    if (move->pNext->key == val)
    {
        removeHead(list);
        move = list.pHead->pNext;
    }
    while (move != nullptr)
    {
        if (move->key == val && move->pPrev != nullptr)
        {
            temp = move->pPrev;
            move->pPrev->pPrev->pNext = move;
            move->pPrev = move->pPrev->pPrev;
            delete temp;
        }
        move = move->pNext;
    }
}
void removeAfter(d_List &list, int val)
{
    d_NODE *move = list.pHead;
    d_NODE *temp;
    if (list.pTail->pPrev->key == val)
    {
        removeTail(list);
    }
    while (move != nullptr)
    {
        if (move->key == val && move->pNext != nullptr)
        {
            temp = move->pNext;
            move->pNext->pNext->pPrev = move;
            move->pNext = move->pNext->pNext;
            delete temp;
        }
        move = move->pNext;
    }
}
bool addPos(d_List &list, int data, int pos)
{
    d_NODE *node = createDoubleNode(data);
    if (node == nullptr)
        return false;
    d_NODE *move = list.pHead->pNext;

    if (pos == 1)
    {
        addHead(list, data);

        return true;
    }

    int count = 2;
    while (move != nullptr)
    {
        if (count++ == pos)
        {
            move->pPrev->pNext = node;
            node->pPrev = move->pPrev;
            move->pPrev = node;
            node->pNext = move;

            return true;
        }
        move = move->pNext;
    }
}
void removePos(d_List &list, int pos)
{
    d_NODE *move = list.pHead->pNext;
    d_NODE *temp;
    if (pos == 1)
    {
        removeHead(list);
        return;
    }

    int count = 2;
    while (move->pNext != nullptr)
    {
        if (count++ == pos)
        {
            temp = move;
            move->pPrev->pNext = move->pNext;
            move->pNext->pPrev = move->pPrev;
            delete temp;

            return;
        }
        move = move->pNext;
    }

    if (count == pos)
    {
        removeTail(list);
    }
}
bool addBefore(d_List &list, int data, int val)
{
    d_NODE *node = createDoubleNode(data);
    if (node == nullptr)
        return false;
    d_NODE *move = list.pHead;
    bool check = false;

    if (move->key == val)
    {
        addHead(list, data);
        move = move->pNext;
        check = true;
    }
    while (move != nullptr)
    {
        if (move->key == val)
        {
            move->pPrev->pNext = node;
            node->pNext = move;
            node->pPrev = move->pPrev;
            move->pPrev = node;
            check = true;
        }
        move = move->pNext;
    }
    return check;
}
bool addAfter(d_List &list, int data, int val)
{
    d_NODE *node = createDoubleNode(data);
    if (node == nullptr)
        return false;
    d_NODE *move = list.pHead;
    bool check = false;

    while (move->pNext != nullptr)
    {
        if (move->key == val)
        {
            node->pPrev = move;
            node->pNext = move->pNext;
            move->pNext->pPrev = node;
            move->pNext = node;
            check = true;
        }
        move = move->pNext;
    }
    if (list.pTail->key == val)
    {
        addTail(list, data);
        check = true;
    }

    return check;
}
int countElements(d_List list)
{
    d_NODE *move = list.pHead;
    int count = 0;
    while (move != nullptr)
    {
        count += 1;
        move = move->pNext;
    }
    return count;
}
d_List reverseList(d_List list)
{
    d_List reversed;
    reversed.pHead = reversed.pTail = nullptr;
    d_NODE *move = list.pHead;

    while (move != nullptr)
    {
        addHead(reversed, move->key);
        move = move->pNext;
    }
    return reversed;
}
void removeDuplicate(d_List &list)
{
    d_NODE *move = list.pHead;
    d_NODE *move2;
    while (move != nullptr)
    {
        move2 = move->pNext;
        while (move2 != nullptr)
        {
            if (move2->key == move->key)
            {
                move2->pPrev->pNext = move2->pNext;
                if (move2->pNext != nullptr)
                {
                    move2->pNext->pPrev = move2->pPrev;
                }
                else
                {
                    list.pTail = move2->pPrev;
                }
            }
            move2 = move2->pNext;
        }
        move = move->pNext;
    }
}
bool removeElement(d_List &list, int key)
{
    bool check = false;
    if (list.pHead->key == key)
    {
        removeHead(list);
        check = true;
    }

    d_NODE *move = list.pHead;
    while (move != nullptr)
    {
        if (move->key == key)
        {
            move->pPrev->pNext = move->pNext;
            if (move->pNext != nullptr)
            {
                move->pNext->pPrev = move->pPrev;
            }
            check = true;
        }
        move = move->pNext;
    }
    return check;
}