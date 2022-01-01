#include <iostream>
using namespace std;

struct d_NODE
{
    int key;
    d_NODE *pNext;
    d_NODE *pPrev;
};

struct d_List
{
    d_NODE *pHead;
    d_NODE *pTail;
};

void printDoubleList(d_List list);
void printReverseDoubleList(d_List list);
d_List createDoubleList(d_NODE *node);
d_NODE *createDoubleNode(int data);
bool addHead(d_List &list, int data);
bool addTail(d_List &list, int data);
void removeHead(d_List &list);
void removeTail(d_List &list);
void removeAll(d_List &list);
void removeBefore(d_List &list, int val);
void removeAfter(d_List &list, int val);
bool addPos(d_List &list, int data, int pos);
void removePos(d_List &list, int pos);
bool addBefore(d_List &list, int data, int val);
bool addAfter(d_List &list, int data, int val);
int countElements(d_List list);
d_List reverseList(d_List list);
void removeDuplicate(d_List &list);
bool removeElement(d_List &list, int key);