#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#define FILE1 "graph1.txt"
#define FILE2 "graph2.txt"
#define FILE3 "graph3.txt"
#define FILE4 "graph4.txt"
using namespace std;

struct NODE
{
    int vertex;
    NODE *adjacent;
};
struct weightedNODE
{
    int vertex;
    int weight;
    NODE *adjacent;
};
typedef struct weightedNODE dNODE;

NODE *createNODE(int vertex);
void printArray(int *a, int n);
//Câu 1

int **readMatrix(string file, int &n);
NODE **matrixToList(int **a, int n);
void printMatrix(int **a, int n);

//Câu 2
void addTail(NODE *&ptr, NODE *node);
NODE **readAdjacentList(string file, int &n);
int **listToMatrix(NODE **list, int n);
void printList(NODE **list, int n);

//Câu 3

bool isDirected(int **matrix, int n);
int getEdges(int **matrix, int n, bool directed);
int **getDegree(int **matrix, int n, bool directed);
void printDegree(int **degs, int n, bool directed);
int *getIsolatedVertices(int **matrix, int n, bool directed);
int *getLeafVertices(int **matrix, int n, bool directed);
bool isComplete(int **matrix, int n, bool directed);
bool isCircular(int **matrix, int n, bool directed);
bool isBigraph(NODE **list, int n, int *&colored);
bool isFullBigraph(NODE **list, int n, bool directed);
int countConnectedComponents(NODE **list, int n,bool directed);
int countCut(NODE **list, int n, bool directed);
int countBrigde(NODE **list, int n, bool directed);
int **convertToUndirected(int **matrix, int n);
int **complementGraph(int** matrix, int n,bool directed);
int **converseGraph(int** matrix, int n);

// Thuật toán
void DFS(NODE **list, int n);
void BFS(NODE **list, int n);
void spanningDFS(NODE **list, int n);