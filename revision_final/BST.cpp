#include "header.h"

NODE *createNODE(int data)
{
    NODE *node = new NODE;
    node->key = data;
    node->left = node->right = nullptr;
    return node;
}

void Insert(NODE *&root, int x)
{
    if (root == nullptr)
        root = createNODE(x);

    if (x < root->key)
        Insert(root->left, x);
    else if (x > root->key)
        Insert(root->right, x);
    else
        return;
}

void preOrder(NODE *root)
{
    if (root == nullptr)
        return;

    cout << root->key << "  ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(NODE *root)
{
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->key << "  ";
}

void inOrder(NODE *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->key << "  ";
    inOrder(root->right);
}

void levelOrder(NODE *root)
{
    if (root == nullptr)
        return;

    queue<NODE *> q;
    q.push(root);

    while (q.size() > 0)
    {
        NODE *curr = q.front();
        cout << curr->key << " ";
        q.pop();

        if (curr->left != nullptr)
            q.push(curr->left);
        if (curr->right != nullptr)
            q.push(curr->right);
    }
    cout << endl;
}

// Đo chiều cao của cây
int height(NODE *root)
{
    if (root == nullptr)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}

int countNode(NODE *root)
{
    if (root == nullptr)
        return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int sumNode(NODE *root)
{
    if (root == nullptr)
        return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

NODE *Search(NODE *root, int x)
{
    if (root == nullptr)
        return root;
    if (x < root->key)
        return Search(root->left, x);
    else if (x > root->key)
        return Search(root->right, x);
    else
        return root;
}

NODE *parentOfMinRight(NODE *&curr)
{
    // Must have 2 children
    NODE *parent = curr;
    curr = curr->right;
    while (curr->left != nullptr)
    {
        parent = curr;
        curr = curr->left;
    }
    return parent;
}

NODE *parentOfMaxLeft(NODE *&curr)
{
    // Must have 2 children
    NODE *parent = curr;
    curr = curr->left;
    while (curr->right != nullptr)
    {
        parent = curr;
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
        // Trường hợp có không hoặc một con xử lý đồng thời
        if (pRoot->left == nullptr)
        {
            pRoot = pRoot->right;
        }
        else if (pRoot->right == nullptr)
        {
            pRoot = pRoot->left;
        }

        // Trường hợp có hai con
        else
        {
            // Tìm node cha của thế mạng
            NODE *move = pRoot;
            NODE *parent = parentOfMinRight(move);

            // Ghi đè giá trị
            pRoot->key = move->key;

            // Xóa node con thế mạng
            NODE *temp = parent->left;
            parent->left = nullptr;
            delete temp;
        }
    }
}
NODE *createTree(int a[], int n)
{
    NODE *root = nullptr;
    for (int i = 0; i < n; i++)
    {
        Insert(root, a[i]);
    }
    return root;
}

void removeTree(NODE *&root)
{
    NODE *temp = root;
    root = nullptr;
    delete root;
}

int heightNode(NODE *root, int value)
{
    if (root == nullptr)
        return -1;

    if (value < root->key)
        return heightNode(root->left, value);
    else if (value > root->key)
        return heightNode(root->right, value);
    else
        return height(root);
}

int Level(NODE *root, NODE *p)
{
    if (root == nullptr)
        return 0;
    if (p->key < root->key)
        return 1 + Level(root->left, p);
    else if (p->key > root->key)
        return 1 + Level(root->right, p);
    else
        return 1;
}

int countLeaf(NODE *root)
{
    if (root == nullptr)
        return 0;
    if (root->left == root->right) // Only equal when null
        return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int countLess(NODE *root, int x)
{
    if (root == nullptr)
        return 0;

    // If bigger, count all nodes in left subtree and traverse to right subtree
    if (x > root->key)
        return 1 + countNode(root->left) + countLess(root->right, x);

    // Or traverse to both direction
    // return 1 + countLess(root->left,x) + countLess(root->right, x);

    // If smaller or equal, traverse to left subtree
    else
        return countLess(root->left, x);
}

int countGreater(NODE *root, int x)
{
    if (root == nullptr)
    {
        return 0;
    }

    // If smaller, count all nodes in right subtree and traverse to left subtree
    if (x < root->key)
        return 1 + countNode(root->right) + countGreater(root->left, x);

    // If bigger or equal, just traverse to right subtree
    else
        return countGreater(root->right, x);
}

//* Should use temp array
bool isBST(NODE *root, NODE *&prev)
{
    // Nếu có thể chạm đến node lá, nghĩa là một số node ở trên đường đi đến nó đã thỏa mãn BST
    if (root == nullptr)
        return true;

    // Nếu như cây con trái không là BST thì return false
    // Nếu là BST thì xét tại node đó rồi xét con phải
    if (isBST(root->left, prev) == false)
        return false;

    // Nếu vi phạm BST thì phát hiện
    if (prev != nullptr && root->key <= prev->key)
        return false;
    prev = root;

    // Cây con phải thì return và duyệt tiếp.
    return isBST(root->right, prev);
}

bool isFull(NODE *root)
{
    if (root != nullptr)
    {
        if (root->left != root->right)
        {
            if (root->left == nullptr or root->right == nullptr)
                return false;
        }

        return isFull(root->left) && isFull(root->right);
    }
    else
        return true;
}

bool isFullBST(NODE *root)
{
    NODE *prev = nullptr;
    return isFull(root) and isBST(root, prev);
}

int power(int x, int y)
{
    int radix = x;
    while (y > 1)
    {
        x *= radix;
        y--;
    }
    return x;
}

bool isPerfect(NODE *root)
{
    int nodes = countNode(root);
    int h = height(root);
    return (nodes == power(2, h) - 1);
}

bool isComplete(NODE *root)
{
    if (root == nullptr)
        return false;

    queue<NODE *> q;
    q.push(root);
    bool end = false;

    while (q.size() > 0)
    {
        NODE *curr = q.front();
        q.pop();

        if (curr->left != nullptr)
            q.push(curr->left);

        // Nếu có con trái bị null thì đánh dấu
        else
            end = true;
        if (curr->right != nullptr)
        {
            // Con phải khác null mà con trái null
            // Thì không phải là CBT
            if (end == true)
                return false;
            q.push(curr->right);
        }
    }

    // Pass hết sau khi duyệt thì là CBT
    return true;
}