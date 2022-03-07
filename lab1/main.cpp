#include "Doubly Linked List.h"

int main()
{
    d_NODE *node = createDoubleNode(10);
    d_List list = createDoubleList(node);
    addHead(list, 10);
    addHead(list, 16);
    addHead(list, 13);
    addHead(list, 14);
    printDoubleList(list);
    printReverseDoubleList(list);
    system("pause");
    return 0;
}