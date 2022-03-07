#include <iostream>
#include <queue>
using namespace std;

struct AVLNode
{
    int p, q;

    AVLNode *pLeft;
    AVLNode *pRight;
};

void balance(AVLNode *&root);
AVLNode *createNode(int p, int q)
{
    AVLNode *node = new AVLNode;
    node->p = p;
    node->q = q;
    node->pLeft = node->pRight = nullptr;
    return node;
}

void levelOrder(AVLNode *root)
{
    queue<AVLNode *> q;
    q.push(root);

    while (q.size() > 0)
    {
        AVLNode *curr = q.front();
        cout << curr->p << "|" << curr->q << " ";
        q.pop();

        if (curr->pLeft != nullptr)
        {
            q.push(curr->pLeft);
        }
        if (curr->pRight != nullptr)
        {
            q.push(curr->pRight);
        }
    }
    cout << endl;
}

// 1 nếu lớn hơn, 0 nếu bằng, -1 nếu nhỏ hơn
int compare(int pInp, int qInp, int p, int q)
{
    int mul1 = pInp * qInp;
    int mul2 = p * q;
    if (mul1 == mul2)
    {
        if (pInp + qInp > p + q)
            return 1;
        else if (pInp + qInp < p + q)
            return -1;
        else
            return 0;
    }
    else if (mul1 > mul2)
        return 1;
    else
        return -1;
}

void Insert(AVLNode *&root, int pInp, int qInp)
{
    //Base case
    if (root == nullptr)
        root = createNode(pInp, qInp);

    //Bé hơn thì đi qua trái
    if (compare(pInp, qInp, root->p, root->q) == -1)
        Insert(root->pLeft, pInp, qInp);
    //Lớn hơn thì đi qua phải
    else if (compare(pInp, qInp, root->p, root->q) == 1)
        Insert(root->pRight, pInp, qInp);
    else
        return;

    balance(root);
}

AVLNode *CreateTree(vector<int> pList, vector<int> qList)
{
    AVLNode *root = nullptr;
    for (int i = 0; i < pList.size(); i++)
    {
        Insert(root, pList[i], qList[i]);
    }
    return root;
}

AVLNode *findParentMaxLeft(AVLNode *&curr)
{
    AVLNode *parent = curr;
    //Kiếm ở cây con trái
    curr = curr->pLeft;
    while (curr->pRight != nullptr)
    {
        parent = curr; // Bằng node trước đó
        curr = curr->pRight;
    }
    return parent;
}

void Remove(AVLNode *&root, int pInp, int qInp)
{
    //Base case
    if (root == nullptr)
        return;

    //Nhỏ hơn thì đi sang trái
    if (compare(pInp, qInp, root->p, root->q) == -1)
        Remove(root->pLeft, pInp, qInp);
    //Lớn hơn thì đi sang phải
    else if (compare(pInp, qInp, root->p, root->q) == 1)
        Remove(root->pRight, pInp, qInp);

    //Tìm thấy
    else
    {
        //Một con và không con
        if (root->pLeft == nullptr)
        {
            root = root->pRight;
        }
        else if (root->pRight == nullptr)
        {
            root = root->pLeft;
        }
        else
        {
            //Ghi đè
            AVLNode *move = root;
            AVLNode *parent = findParentMaxLeft(move);
            root->p = move->p;
            root->q = move->q;
            //Xóa
            if (parent->pRight == move)
            {
                AVLNode *temp = parent->pRight;
                parent->pRight = nullptr;
                delete temp;
            }
            else if (parent->pLeft == move)
            {
                AVLNode *temp = parent->pLeft;
                parent->pLeft = nullptr;
                delete temp;
            }
        }
    }

    balance(root);
}

void RR(AVLNode *&root)
{

    // cout << "Right rotate at " << root->p << "|" << root->q << endl;
    AVLNode *temp = root->pLeft;
    root->pLeft = temp->pRight;
    temp->pRight = root;
    root = temp;
}

void LR(AVLNode *&root)
{
    // cout << "Left rotate at " << root->p << "|" << root->q << endl;
    AVLNode *temp = root->pRight;
    root->pRight = temp->pLeft;
    temp->pLeft = root;
    root = temp;
}

int height(AVLNode *root)
{
    if (root == nullptr)
        return 0;
    int lheight = height(root->pLeft);
    int rheight = height(root->pRight);

    if (lheight > rheight)
        return 1 + lheight;
    else
        return 1 + rheight;
}

void balance(AVLNode *&root)
{
    int lheight = height(root->pLeft);
    int rheight = height(root->pRight);
    int delta = lheight - rheight;

    //Lệch trái
    if (delta > 1)
    {
        if (height(root->pLeft->pRight) > height(root->pLeft->pLeft)) //trái phải
        {
            LR(root->pLeft);
        }
        RR(root);
    }

    //Lệch phải
    else if (delta < -1)
    {
        if (height(root->pRight->pLeft) > height(root->pRight->pRight)) //phải trái
        {
            RR(root->pRight);
        }
        LR(root);
    }
}

void Bai01()
{
    vector<int> pList = {5, 4, 4, 2, 4, 4};
    vector<int> qList = {6, 9, 8, 6, 7, 6};

    AVLNode *root = CreateTree(pList, qList);
    Remove(root, 4, 7);
    levelOrder(root);
}

void printMatrix(vector<vector<bool>> adj)
{
    for (int i = 0; i < adj.size(); i++)
    {
        for (int j = 0; j < adj.size(); j++)
        {
            // if(adj[i][j] == true)
            //     cout<<"true"<< "  ";
            // else
            //     cout<<"false"<<"  ";
            cout << adj[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    Bai01();

    system("pause");
    return 0;
}