<link rel="stylesheet" href="main.css">

# Binary Search Tree

## General

Cây tìm kiếm:

Cây nhị phân tìm kiếm là cây có các tính chất sau:

- Node con trái của một node n bất kỳ luôn có khóa nhỏ hơn node n đó.
- Node con phải của một node n bất kỳ luôn có khóa lớn hơn node n đó.
- Node con trái và phải của node bất kỳ, nếu là một cây nhị phân, thì cây đó cũng phải là cây nhị phân tìm kiếm (thỏa hai tính chất trên). Và mọi key của cả cây con trái, sẽ bé hơn root, cũng như mọi key của cả cây con phải sẽ lớn hơn root.

Ngoài ra, nó còn là một Full Binary Tree.

Không được có hai node có khóa trùng nhau. (Giống như là khóa chính trong SQL, chúng là unique và có thể có nhiều trường).

Cây nhị phân tìm kiếm phụ thuộc vào dữ liệu đầu vào, nếu như dữ liệu ấy là xấu thì sẽ dẫn đến các operation thực hiện trên nó sẽ có chi phí cao.

<img src="../img/Tree16.png">

Do nó được sắp xếp theo thứ tự như vậy mà các công việc như tìm kiếm, tìm max, min được thực hiện nhanh chóng hơn trong đa số các trường hợp. Nếu không được sắp xếp, mỗi lần tìm kiếm khóa nào đó ta phải đi so sánh rất mất thời gian.

Fact thú vị: khi duyệt giữa cây nhị phân tìm kiếm, do cấu trúc của nó được sắp theo thứ tự là left root right nên kết quả của phép duyệt sẽ là một danh sách các số có thứ tự.

Tìm kiếm một phần tử trong cây nhị phân cũng tương tự như tìm kiếm nhị phân trên mảng. Chúng ta sẽ so sánh phần tử root so với phần tử cần tìm, nếu nó bằng thì tại root chính là phần tử ta đang tìm kiếm. Nếu nó bé hơn thì ta duyệt cây con bên trái, ngược lại ta duyệt cây con bên phải. Mỗi lần so sánh là chúng ta chọn đi sang trái hoặc phải, có nghĩa là ta bỏ một trong hai cây con và các bước duyệt qua chúng. Điều này làm giảm đáng kể số lần duyệt và so sánh của thuật toán tìm kiếm.

**Question** : Nếu nó giống nhau vậy thì tìm kiếm trên BST và tìm kiếm nhị phân trên mảng cái nào nhanh hơn cho một danh sách dữ liệu giống nhau.

**Answer:** BST sẽ nhanh hơn trong đa số trường hợp, nhưng đôi khi vẫn có trường hợp xấu.

## Implementation

### Search

```c++
NODE *search(NODE *pRoot, int x)
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
```

Ta bắt đầu duyệt từ node gốc nào đó (thường thì ta sẽ giữa một node làm node giữa của BST). Nếu giá trị cần tìm nhỏ hơn nút gốc, tìm bên cây con trái. Ngược lại tìm bên cây con phải. Trường hợp suy biến là trả về giá trị node gốc khi node đó rỗng (node lá) hoặc là node cần tìm.

Độ phức tạp dễ thấy là $O(log_2n)$. Worst cây là khi nó là một cây thẳng, dẫn đến $O(n)$.

### Insert

Ý tưởng của thuật toán là ta sẽ luôn thêm node ở các lá. Do đó mà ta sẽ đào cây đến khi gặp một node rỗng (node lá) thì ta thêm tại đó. Mỗi lần duyệt ta sẽ kiểm tra node cần thêm, nếu nó nhỏ hơn node gốc thì ta duyệt cây con bên trái, ngược lại duyệt cây con bên phải. Nếu tại node đó rỗng, ta sẽ tạo một node mới. Cuối cùng, sau khi duyệt xong node, ta trả về node gốc để quay ngược lại node bắt đầu.
**Code:**

```c++
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
```

Để implement một cách tự nhiên nhất, giá trị trả về nên là int. Với 1 là thêm thành công và 0 là thêm thất bại.

**Question** : hàm trong slide HCMUS không trả về root.

**Answer** : Một số phiên bản return về root để hoàn trả lại node hiện tại hoặc node vừa được thêm.

Độ phức tạp của thuật toán này là $O(n)$ cho trường hợp xấu nhất. Trường hợp xấu nhất xảy ra khi cây là một cây thẳng tuyến tính. Trong trường hợp thông thường thì độ phức tạp là $O(log_2n)$.

### Delete

Có ba khả năng xảy ra khi delete một node trong BST:

#### Node đó là một lá

Chúng ta chỉ đơn giản xóa nó ra khỏi cây.

<img src="../img/Tree17.png">

#### Node đó có duy nhất một con

Sao chép con đó cho node cần xóa và xóa node con.

<img src="../img/Tree18.png">

#### Node có 2 con.

Ta đi tìm node con nhỏ nhất trong cây con phải của node cần xóa hoặc node con lớn nhất trong cây con trái. Sau đó swap node cần xóa với node con vừa tìm, rồi xóa node con.

Về độ phức tạp thuật toán, trường hợp thường gặp là $O(h)$ với h là chiều cao của cây và có giá trị $\geq log_2(n + 1)$, khi đó ta phải duyệt qua mọi node để đến node lá. Nếu cây là một cây thẳng, thì độ phức tạp trở thành $O(n)$.

**Code tìm phần tử nhỏ nhất cây con phải:**

```c++
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
```

**Code tìm phần tử lớn nhất cây con trái:**

```c++
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
```

**Code xóa một node trong BST:**

```c++
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
}
```

### Rotation

BST có hai thao tác quan trọng là xoay cây trái và phải. Mỗi khi ta xoay cây theo chiều nào, rồi xoay cây theo chiều ngược lại, thì ta sẽ được một cây nhị phân tìm kiếm như ban đầu. Tức là nếu xoay trái, rồi xoay phải, cây sẽ không đối.

Thuật toán xoay cây là một thuật toán local, nó chỉ thao tác xung quanh một node nào đó và các node con của nó, chứ không ảnh hưởng đến parent hoặc sibling của nó. Vì tính chất này mà Rotation mới giữ được tính chất của BST sau khi xoay cây.

#### Left Rotation

Thuật toán xoay cây trái sẽ bắt đầu quanh một node nào đó. Chúng ta sẽ xét thêm cả node con phải của node đó. Ta gọi node đang xét là A, và node con phải là B.

Đầu tiên, ta thay A bằng B, và A thành con trái của B. Điều này vẫn giúp chúng ta maintain được tính chất của BST. Tiếp theo, con trái của A thì vẫn là con trái của A. Con phải của B vẫn là con phải của B. Hai cây/node con này vẫn nằm ở vị trí mà nó vốn có, không vi phạm tính chất của BST. Tuy nhiên vẫn còn một con nữa chưa sắp, đó là con trái của B, gọi là C. Node này có giá trị lớn hơn A và bé hơn B.
Tức là A $<$ C $<$ B.

Do nó lớn hơn A, ta đặt nó là con phải của A trong phép xoay cây ở trên.

> Điều kiện của phép xoay trái là node cần xoay phải có con phải.

<img src="../img/Tree20.png">

**Code:**

```c++
void LR(NODE *&pRoot)
{
    NODE *temp = pRoot->right;
    pRoot->right = temp->left;
    temp->left = pRoot;
    pRoot = temp;
}
```

#### Right Rotation

Để xoay phải cây ta cũng xét tương tự xoay trái tại một node nào đó. Và ta sẽ xét thêm node con trái của node cần xoay. Ta gọi node đang xét là A và node con trái là B.

Tương tự xoay trái, ta thay A bằng B. Con trái của A vẫn là con trái của A, con phải của B vẫn là con phải của B. Tuy nhiên con phải của A sẽ trở thành con trái của B. Tức là T2 trong hình sẽ thành con trái của B.

> Điều kiện của phép xoay phải là node cần xoay phải có con trái.

<img src="../img/Tree21.png">

**Code:**

```c++
void RR(NODE *&pRoot)
{
    NODE *temp = pRoot->left;
    pRoot->left = temp->right;
    temp->right = pRoot;
    pRoot = temp;
}
```

Độ phức tạp của các thuật toán xoay cây là $O(1)$.

### Is BST ?

Thuật toán chứng minh một cây là cây nhị phân tìm kiếm có hai phần.

Phần đầu tiên là chứng minh nó là cây nhị phân tìm kiếm cục bộ, tức là xét với mỗi node thì nó đều nhỏ hơn con phải và lớn hơn con trái.

Phần thứ hai là xét toàn cục, với mỗi node thì tìm node nhỏ nhất của cây con bên phải so với nó, nếu lớn hơn thì là BST. Tương tự tìm node lớn nhất của cây con bên trái, nếu nhỏ hơn thì là BST.

**Code:**

```c++
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
```

Ngoài ra cũng còn một cách kiểm tra nữa sử dụng một mảng phụ. Ta tiến hành duyệt giữa cây, mỗi lần đến một node thì lưu node đó vào mảng. Nếu mảng của chúng ta giảm dần (đệ quy cho ra mảng ngược) hoặc tăng dần (duyệt mảng ngược) thì là BST. Cách này cũng có thể kiểm tra phần tử trùng trong cây bằng cách xét hai phần tử liền kề.

**Code duyệt giữa và thêm vào mảng phụ:**

```c++
void inorderToArray(NODE *pRoot, int *a, int &n)
{
    if (pRoot == nullptr)
        return;

    inorderToArray(pRoot->left, a, n);
    a[--n] = pRoot->key;
    inorderToArray(pRoot->right, a, n);
}
```

**Code chứng minh BST:**

```c++
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
```

### Is Full BST ?

Để chứng minh một cây nhị phân tìm kiếm là đầy đủ thì cần hai điều kiện: nó là BST và nó là cây nhị phân đầy đủ.

Để chứng minh nó là BST thì ta gọi hàm isBST ở trên. Để chứng minh nó là cây nhị phân đầy đủ thì cần viết hàm kiểm tra xem mỗi node có thỏa mãn tính chất sở hữu 0 hoặc 2 con không. Nếu node nào có 1 con thì không phải là cây nhị phân đầy đủ.

**Code:**

```c++
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
```

### Count less

Đếm số node mà bé hơn một giá trị cho trước trong cây.

```c++
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
```

### Count Greater

Đếm số node lớn hơn một giá trị cho trước

```c++
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

```
# Complexity

<img src="../img/Tree22.png">