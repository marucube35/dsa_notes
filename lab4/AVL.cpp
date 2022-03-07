#include <iostream>
using namespace std;
struct NODE
{
    int key;
    NODE *left;
    NODE *right;
    int height;
};
void Insert(NODE *&pRoot, int x);

NODE *createNode(int data)
{
    NODE *node = new NODE;
    node->key = data;
    node->left = node->right = nullptr;
    node->height = 0;
    return node;
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

void RR(NODE *&pRoot)
{
    NODE *temp = pRoot->left;
    pRoot->left = temp->right;
    temp->right = pRoot;
    pRoot = temp;
}

void LR(NODE *&pRoot)
{
    NODE *temp = pRoot->right;
    pRoot->right = temp->left;
    temp->left = pRoot;
    pRoot = temp;
}

void balanceTree(NODE *&pRoot)
{
    int hl = Height(pRoot->left);
    int hr = Height(pRoot->right);
    int delta = hl - hr;

    //lech trai
    if (delta > 1)
    {
        if (Height(pRoot->left->left) < Height(pRoot->left->right))
        {
            LR(pRoot->left);
        }
        RR(pRoot);
    }
    else if (delta < -1)
    {
        if (Height(pRoot->right->right) < Height(pRoot->right->left))
        {
            RR(pRoot->right);
        }
        LR(pRoot);
    }
    else
    {
    }
}

void Insert(NODE *&pRoot, int x)
{
    if (pRoot == nullptr)
        pRoot = createNode(x);

    if (x < pRoot->key)
    {
        Insert(pRoot->left, x);
    }

    else if (x > pRoot->key)
    {
        Insert(pRoot->right, x);
    }
    else
    {
        return;
    }

    balanceTree(pRoot);
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
            //search for IS
            NODE *move = pRoot;
            NODE *parent = searchRightMin(move);
            //overwrite on root
            pRoot->key = move->key;
            //delete old IS
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
    if (pRoot != nullptr)
        balanceTree(pRoot);
}

bool isAVL(NODE *pRoot)
{
    if (pRoot != nullptr)
    {
        int hl = Height(pRoot->left);
        int hr = Height(pRoot->right);
        int delta = hl - hr;

        if (delta > 1 || delta < -1)
            return false;
        return isAVL(pRoot->left) && isAVL(pRoot->right);
    }
    else
    {
        return true;
    }
}

int main(int argc, char **argv)
{
    int a[7] = {15, 10, 11, 17, 19, 21, 8};
    NODE *pRoot = createTree(a, 7);
    LNR(pRoot);
    cout << "Is AVL ? " << isAVL(pRoot) << endl;
    
    Remove(pRoot, 15);
    LNR(pRoot);
    cout << "Is AVL ? " << isAVL(pRoot) << endl;

    system("pause");
    return 0;
}