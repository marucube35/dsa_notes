#include "header.h"

int main(int argc, char *argv[])
{
    int nodes = 0;
    NODE **list = readAdjacentList(FILE4, nodes);
    int **matrix = listToMatrix(list, nodes);
    printMatrix(matrix,nodes);
    printList(list,nodes);

    spanningDFS(list,nodes);


    system("pause");
    return 0;
}
