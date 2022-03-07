#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct NODE
{
    int key;
    NODE *left;
    NODE *right;
};

NODE *createNode(int data)
{
    NODE *node = new NODE;
    node->key = data;
    node->left = node->right = nullptr;
    return node;
}
void Insert(NODE *&pRoot, int x)
{
    //base case
    if (pRoot == nullptr)
    {
        pRoot = createNode(x);
        return;
    }

    //traverse to sub left tree
    if (x < pRoot->key)
    {
        Insert(pRoot->left, x);
    }
    //traverse to right left tree
    else if (x > pRoot->key)
    {
        Insert(pRoot->right, x);
    }
}

void NLR(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
    {
        return;
    }

    cout << pRoot->key << "\t";
    NLR(pRoot->left);
    NLR(pRoot->right);
}

void LNR(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
    {
        return;
    }

    LNR(pRoot->left);
    cout << pRoot->key << "\t";
    LNR(pRoot->right);
}

void LRN(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
    {
        return;
    }

    NLR(pRoot->left);
    NLR(pRoot->right);
    cout << pRoot->key << "\t";
}

void levelOrder(NODE *pRoot)
{
    queue<NODE *> Q;
    NODE *move = pRoot;
    while (move != nullptr)
    {
        cout << move->key << "\t";
        if (move->left != nullptr)
        {
            Q.push(move->left);
        }
        if (move->right != nullptr)
        {
            Q.push(move->right);
        }

        if (Q.size() == 0)
            break;

        move = Q.front();
        Q.pop();
    }
    cout << endl;
}

int Height(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
        return 0;
    //compare subtree's height
    int leftHeight = Height(pRoot->left);
    int rightHeight = Height(pRoot->right);
    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}

int countNode(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
        return 0;

    //counting nodes of subtree
    return 1 + countNode(pRoot->left) + countNode(pRoot->right);
}

int sumNode(NODE *pRoot)
{
    //base case
    if (pRoot == nullptr)
        return 0;

    return pRoot->key + sumNode(pRoot->left) + sumNode(pRoot->right);
}

NODE *Search(NODE *pRoot, int x)
{
    //base case
    if (pRoot == nullptr)
        return nullptr;

    if (x < pRoot->key)
        Search(pRoot->left, x);
    else if (x > pRoot->key)
        Search(pRoot->right, x);
    else
        return pRoot;
}

NODE *searchRightMin(NODE *&curr)
{
    NODE *parent = curr;
    //search in right subtree
    curr = curr->right;
    while (curr->left != nullptr)
    {
        parent = curr; //parent be prev root
        curr = curr->left;
    }
    return parent;
}

NODE *searchLeftMax(NODE *&curr)
{
    NODE *parent = curr;
    //search in left subtree
    curr = curr->left;
    while (curr->right != nullptr)
    {
        parent = curr; //parent be prev root
        curr = curr->right;
    }
    return parent;
}

void Remove(NODE *&pRoot, int x)
{
    if (pRoot == nullptr)
        return;

    if (x < pRoot->key)
        Remove(pRoot->left, x);
    else if (x > pRoot->key)
        Remove(pRoot->right, x);
    else
    {
        NODE *temp = pRoot;
        //zero and one children
        if (pRoot->left == nullptr)
        {
            pRoot = pRoot->right;
        }
        else if (pRoot->right == nullptr)
        {
            pRoot = pRoot->left;
        }
        //two children
        else
        {
            //search for min in right subtree
            NODE *move = pRoot;
            NODE *parent = searchRightMin(move);
            //overwrite on root
            pRoot->key = move->key;
            //delete min in right subtree
            if (parent->left == move)
            {
                temp = parent->left;
                parent->left = nullptr;
            }
            else if (parent->right == move)
            {
                temp = parent->right;
                parent->right = nullptr;
            }
        }
        delete temp;
    }
}

NODE *createTree(int a[], int n)
{
    NODE *pRoot = nullptr;
    for (int i = 0; i < n; i++)
    {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

void removeTree(NODE *&pRoot)
{
    NODE *temp = pRoot;
    pRoot = nullptr;
    delete temp;
}

int heightNode(NODE *pRoot, int value)
{
    if (pRoot == nullptr)
        return -1;

    if (value < pRoot->key)
        return heightNode(pRoot->left, value);
    else if (value > pRoot->key)
        return heightNode(pRoot->right, value);
    else
    {
        return Height(pRoot);
    }
}

int Level(NODE *pRoot, NODE *p)
{
    if (pRoot == nullptr || p == nullptr)
        return 0;
    if (p->key < pRoot->key)
        return 1 + Level(pRoot->left, p);
    else if (p->key > pRoot->key)
        return 1 + Level(pRoot->right, p);
    else
    {
        return 1;
    }
}

int countLeaf(NODE *pRoot)
{
    if (pRoot == nullptr)
        return 0;
    if (pRoot->left == pRoot->right)
        return 1;
    return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}

int countLess(NODE* pRoot, int x)
{
    if(pRoot == nullptr)
        return 0;
    if(x > pRoot->key)
        return 1 + countNode(pRoot->left) + countLess(pRoot->right,x);
    else if (x < pRoot->key)
        return countLess(pRoot->left,x);
    else 
        return countNode(pRoot->left);
}

int countGreater(NODE *pRoot, int x)
{
    if (pRoot == nullptr)
        return 0;
    if (x < pRoot->key)
        return 1 + countNode(pRoot->right) + countGreater(pRoot->left,x);
    else if (x > pRoot->key)
        return countGreater(pRoot->right, x);
    else
        return countNode(pRoot->right);
}

bool isBST(NODE *pRoot)
{
    if (pRoot != nullptr)
    {
        NODE *rightMin = pRoot;
        NODE *leftMax = pRoot;

        if (pRoot->left != nullptr)
            searchLeftMax(leftMax);
        else if (pRoot->right != nullptr)
            searchRightMin(rightMin);

        if ((pRoot->left != nullptr && pRoot->left->key > pRoot->key) 
        || (pRoot->right != nullptr && pRoot->right->key < pRoot->key))
            return false;
        else if (rightMin->key < pRoot->key || leftMax->key > pRoot->key)
            return false;
        else
            return isBST(pRoot->left) && isBST(pRoot->right);
    }
    //if it's null, it means it's parent is satisfy BST
    else
        return true;
}

void inorderToArray(NODE *pRoot, int *a, int &n)
{
    if (pRoot == nullptr)
        return;

    inorderToArray(pRoot->left, a, n);
    a[--n] = pRoot->key;
    inorderToArray(pRoot->right, a, n);
}

bool isBST2(NODE *pRoot)
{
    int n = countNode(pRoot);
    int temp = n;
    int *a = new int[n];
    inorderToArray(pRoot, a, temp);

    for (int i = 0; i < n; i++)
    {
        if (a[i] <= a[i + 1])
            return false;
    }
    return true;
}

bool isFull(NODE* pRoot)
{
    if(pRoot != nullptr)
    {
        if((pRoot->left == pRoot->right) || (pRoot->left != nullptr && pRoot->right != nullptr))
            return isFull(pRoot->left) && isFull(pRoot->right);
        else
            return false;
    }
    else
    {
        return true;
    }
}

bool isFullBST(NODE*pRoot)
{
    return isFull(pRoot) && isBST2(pRoot);
}

int main(int argc, char **argv)
{
    int a[6] = {15, 10, 19, 11, 17, 22};
    int b[6] = {15, 14, 13, 12, 11, 10};
    int c[6] = {10, 11, 12, 13, 14, 15};
    // NODE *pRoot = createTree(a, 6);
    NODE *pRoot = new NODE;
    pRoot->key = 10;
    pRoot->left = createNode(7);
    pRoot->left->left = createNode(6);
    pRoot->left->right = createNode(8);
    pRoot->right = createNode(27);
    pRoot->right->left = createNode(19);
    pRoot->right->left->left = createNode(15);
    pRoot->right->left->left->left = createNode(14);
    pRoot->right->left->left->right = createNode(18);
    pRoot->right->left->right = createNode(23);
    pRoot->right->right = createNode(35);

    LNR(pRoot);
    cout << endl;
    cout << "Is this BST tree ? " << isBST2(pRoot) << endl;
    cout << "Is this Full BST tree ? " << isFullBST(pRoot) << endl;
    cout << "Height: " << Height(pRoot) << endl;
    cout << "Total Node(s): " << countNode(pRoot) << endl;
    cout << "Total Leaves: " << countLeaf(pRoot) << endl;
    cout << "Sum Node(s): " << sumNode(pRoot) << endl;
    cout << "Search 15:" << Search(pRoot, 15)->key << endl;
    cout << "Height of 19:" << heightNode(pRoot, 19) << endl;
    cout << "Level of 10: " << Level(pRoot, Search(pRoot, 10)) << endl;
    cout << "Number of node(s) less than 36: " << countLess(pRoot, 36) << endl;
    cout << "Number of node(s) greater than 10: " << countGreater(pRoot, 10) << endl;
    // LNR(pRoot);

    system("pause");
    return 0;
}