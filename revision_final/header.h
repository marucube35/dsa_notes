#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
// struct NODE
// {
//     int key;
//     NODE *left;
//     NODE *right;
// };
struct NODE
{
    int key;
    NODE *left;
    NODE *right;
    int height;
};
struct VERTEX
{
    int key;
    VERTEX *adjacent;
};

//BST

NODE *createNODE(int data);
void Insert(NODE *&root, int x);
void preOrder(NODE *root);
void postOrder(NODE *root);
void inOrder(NODE *root);
void levelOrder(NODE *root);
int height(NODE *root);
int countNode(NODE *root);
int sumNode(NODE *root);
NODE *Search(NODE *root, int x);

NODE *parentOfMinRight(NODE *&root);
NODE *parentOfMaxLeft(NODE *&root);
void Remove(NODE *&root, int x);
NODE *createTree(int a[], int n);
void removeTree(NODE *&root);
int heightNode(NODE *root, int value);
int Level(NODE *root, NODE *p);
int countLeaf(NODE *root);
int countLess(NODE *root, int x);
int countGreater(NODE *root, int x);
bool isBST(NODE *root, NODE *&prev);
bool isFull(NODE *root);
bool isFullBST(NODE *root);
bool isPerfect(NODE* root);
bool isComplete(NODE *root);

// AVL
void RR(NODE *&root);
void LR(NODE *&root);
void AVLInsert(NODE *&root, int x);
void AVLRemove(NODE *&root, int x);
NODE *createAVLTree(int a[], int n);
bool isBalanced(NODE *root);
bool isAVL(NODE *root);

// Graph

int **readMatrix(string file, int &n);
void printMatrix(int **matrix, int n);
VERTEX **readList(string file, int &n);
void printList(VERTEX **list, int n);