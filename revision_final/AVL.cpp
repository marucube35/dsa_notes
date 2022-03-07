#include "header.h"

NODE *createANODE(int data)
{
    NODE *node = new NODE;
    node->key = data;
    node->left = node->right = nullptr;
    node->height = 0;
    return node;
}

void RR(NODE *&root)
{
    cout << "Right rotate at " << root->key << endl;
    if (root->left == nullptr)
        return;

    NODE *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}

void LR(NODE *&root)
{
    cout << "Left rotate at " << root->key << endl;
    if (root->right == nullptr)
        return;

    NODE *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

void balance(NODE *&root)
{
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int delta = leftHeight - rightHeight;

    // Lệch trái
    if (delta > 1)
    {
        if (height(root->left->right) > height(root->left->left)) //Trái phải
        {
            LR(root->left);
        }
        RR(root);
    }

    // Lệch phải
    else if (delta < -1)
    {
        if (height(root->right->left) > height(root->right->right)) // Phải trái
        {
            RR(root->right);
        }
        LR(root);
    }
}

NODE *createAVLTree(int a[], int n)
{
    NODE *root = nullptr;
    for (int i = 0; i < n; i++)
    {
        AVLInsert(root, a[i]);
    }
    return root;
}

void AVLInsert(NODE *&root, int x)
{
    if (root == nullptr)
        root = createANODE(x);

    if (x < root->key)
        AVLInsert(root->left, x);
    else if (x > root->key)
        AVLInsert(root->right, x);
    else
        return;

    balance(root);
}

void AVLRemove(NODE *&root, int x)
{
    if (root == nullptr)
        return;

    // Searching
    if (x < root->key)
        Remove(root->left, x);
    else if (x > root->key)
        Remove(root->right, x);

    // Remove
    else
    {

        if (root->left == nullptr)
        {
            root = root->right;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
        }
        else
        {
            // Overwrite
            NODE *move = root;
            NODE *parent = parentOfMaxLeft(move);
            root->key = move->key;

            // Delete
            if (parent->right == move)
            {
                NODE *temp = parent->right;
                parent->right = nullptr;
                delete temp;
            }
            else
            {
                NODE *temp = parent->left;
                parent->left = nullptr;
                delete temp;
            }
        }
    }

    balance(root);
}

bool isBalanced(NODE *root)
{
    if (root != nullptr)
    {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        int delta = leftHeight - rightHeight;
        if (delta > 1 or delta < -1)
            return false;
        return isBalanced(root->left) and isBalanced(root->right);
    }
    else
        return true;
}

bool isAVL(NODE* root)
{
    NODE* prev = nullptr;
    return isBalanced(root) and isBST(root,prev);
}