#include "header.h"

//! Các thuật toán bên dưới bỏ qua trường hợp đa đồ thị có hướng.

//Do chỉ xét đơn đồ thị nên đối xứng là vô hướng
bool isDirected(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
                return true;
        }
    }
    return false;
}

int getEdges(int **matrix, int n, bool directed)
{
    int edges = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            edges += matrix[i][j];
        }
    }
    if (directed)
        return edges;
    return edges / 2;
}

void printDegree(int **degs, int n, bool directed)
{
    for (int i = 0; i < n; i++)
    {
        if (directed)
        {
            cout << "In-Deg(" << i << ") = " << degs[i][1] << "  , ";
            cout << "Out-Deg(" << i << ") = " << degs[i][0] << endl;
        }
        else
        {
            cout << "Deg(" << i << ") = " << degs[i][0] << endl;
        }
    }
}

int **getDegree(int **matrix, int n, bool directed)
{
    int **deg = new int *[n];
    for (int i = 0; i < n; i++)
    {
        deg[i] = new int[2]{0};
    }

    int i = 0;
    while (i < n)
    {
        if (directed)
        {
            int j = 0;
            while (j < n)
            {
                deg[i][0] += matrix[i][j]; //Cột 0 là bậc ra
                deg[j][1] += matrix[i][j]; //Cột 1 là bậc vào
                j++;
            }
        }
        else
        {
            deg[i] = new int;
            deg[i][0] = 0;
            int j = 0;
            while (j < n)
            {
                deg[i][0] += matrix[i][j];
                j++;
            }
        }
        i++;
    }

    return deg;
}

int *getIsolatedVertices(int **matrix, int n, bool directed)
{
    int *isolated = new int[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //Có hướng thì kiểm tra thêm cột
            if ((matrix[i][j] == 1) ||
                (directed == true && matrix[j][i] == 1))
            {
                //Nếu vi phạm thì cho là 0 và xét node kế tiếp
                isolated[i] = 0;
                break;
            }
            else
                isolated[i] = 1;
        }
    }

    return isolated;
}

int *getLeafVertices(int **matrix, int n, bool directed)
{
    int *leaves = new int[n];
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            //Có hướng thì xét thêm cột
            if (directed)
                sum += matrix[i][j] + matrix[j][i];
            else
                sum += matrix[i][j];
        }
        if (sum == 1)
            leaves[i] = 1;
        else
            leaves[i] = 0;
    }

    return leaves;
}

bool isComplete(int **matrix, int n, bool directed)
{
    int **deg = getDegree(matrix, n, directed);

    for (int i = 0; i < n; i++)
    {
        int temp;
        if (directed)
        {
            temp = deg[i][0] + deg[i][1];
        }
        else
        {
            temp = deg[i][0];
        }

        if (temp != n - 1)
            return false;
    }
    return true;
}

bool isCircular(int **matrix, int n, bool directed)
{
    int **deg = getDegree(matrix, n, directed);

    for (int i = 0; i < n; i++)
    {
        int temp;
        if (directed)
        {
            temp = deg[i][0] + deg[i][1];
        }
        else
        {
            temp = deg[i][0];
        }

        if (temp != 2) //Bậc các đỉnh phải là 2
            return false;
    }
    return true;
}

void findUncolored(queue<int> &q, int *colored, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (colored[i] == 0)
        {
            q.push(i);
            break;
        }
    }
}

bool isBigraph(NODE **list, int n, int *&colored)
{
    //Số 1 là màu đỏ, -1 là màu xanh
    colored = new int[n]{0};

    queue<int> q;
    q.push(0);
    colored[0] = 1;

    while (q.size() > 0)
    {
        int curr = q.front();
        q.pop();

        NODE *move = list[curr];
        while (move != nullptr)
        {
            //Nếu đỉnh kề của đỉnh hiện tại đã bị tô màu
            if (colored[move->vertex] != 0)
            {
                //Và trùng màu với đỉnh hiện tại
                if (colored[curr] == colored[move->vertex])
                {
                    cout << "---------------------" << endl;
                    cout << "Colored: ";
                    printArray(colored, n);
                    return false; //Thì là hai đỉnh cùng một tập
                }
                //Hoặc đỉnh hiện tại chưa được tô màu
                if (colored[curr] == 0)
                {
                    //Thì tô màu trái ngược với đỉnh kề của nó
                    colored[curr] = -1 * colored[move->vertex];
                }
            }
            //Nếu không thì tiến hành tô màu
            else
            {
                if (colored[curr] == 1)
                {
                    colored[move->vertex] = -1;
                }
                else
                {
                    colored[move->vertex] = 1;
                }
                q.push(move->vertex);
            }

            move = move->adjacent;
        }
        //Dò tìm đỉnh chưa tô màu
        if (q.size() == 0)
            findUncolored(q, colored, n);
    }

    cout << "---------------------" << endl;
    cout << "Colored: ";
    printArray(colored, n);
    return true;
}

//Do bỏ qua đa đồ thị có hướng nên không xét strongly connected
bool isConnected(int **matrix, int n, bool directed)
{
    //Kiểm tra xem có bất kỳ đỉnh cô lập nào không
    int *isolated = getIsolatedVertices(matrix, n, directed);
    for (int i = 0; i < n; i++)
    {
        if (isolated[i] == 1)
            return false;
    }
    return true;
}

bool isFullBigraph(NODE **list, int n, bool directed)
{
    int **matrix = listToMatrix(list, n);

    //Do là đồ thị đủ nên cần phải liên thông
    if (!isConnected(matrix, n, directed))
        return false;

    //Lấy mảng màu và kiểm tra lưỡng phân
    int *colored;
    if (!isBigraph(list, n, colored))
        return false;

    //Lấy tổng số node của mỗi màu
    int one = 0, two = 0;
    for (int i = 0; i < n; i++)
    {
        if (colored[i] == 1)
            one += 1;
        else
            two += 1;
    }

    //Lấy tổng bậc của các đỉnh
    int **degs = getDegree(matrix, n, false);
    for (int i = 0; i < n; i++)
    {
        //Do bỏ qua đa đồ thị có hướng
        //nên đồ thị lưỡng phân đủ sẽ luôn là đồ thị vô hướng
        //Vì vậy chỉ cần xét bậc của đồ thị vô hướng
        int deg = degs[i][0];
        if (colored[i] == 1 && deg != two)
            return false;
        else if (colored[i] == -1 && deg != one)
            return false;
    }
    return true;
}

//* Tham khảo: https://www.baeldung.com/cs/determine-graph-is-tree
bool isDirectedTree(NODE **component, int n)
{
    int **matrix = listToMatrix(component, n);
    int **degs = getDegree(matrix, n, true);
    int root = 0;

    for (int i = 0; i < n; i++)
    {
        //Nếu có đỉnh cô lập thì bỏ qua do không thuộc thành phần liên thông
        if (degs[i][0] + degs[i][1] == 0)
            continue;

        //Nếu có đỉnh gốc (không có cạnh đi vào) thì đánh dấu
        if (degs[i][1] == 0)
            root += 1;

        //Nếu đỉnh có nhiều hơn một cha thì false
        if (degs[i][1] > 1)
            return false;
    }

    //Nếu có nhiều hơn một đỉnh gốc hoặc không có đỉnh gốc nào thì false
    if (root != 1)
        return false;
    return true;
}

bool isUndirectedTree(NODE **component, int n)
{
    int **matrix = listToMatrix(component, n);
    int **degs = getDegree(matrix, n, false);
    int sum_deg = 0;
    int vertices = 0;

    for (int i = 0; i < n; i++)
    {
        //Nếu có đỉnh cô lập thì bỏ qua do không thuộc thành phần liên thông
        if (degs[i][0] == 0)
            continue;
        sum_deg += degs[i][0];
        vertices += 1;
    }

    //Số cạnh bằng tổng số bậc chia 2
    int edges = sum_deg / 2;

    //Nếu đồ thị có n - 1 cạnh thì là cây, do đã liên thông và vô hướng
    if (edges == vertices - 1)
        return true;
    return false;
}

int countConnectedComponents(NODE **list, int n, bool directed)
{
    //Chỉ xét vô hướng ở phạm vi toàn cục, bỏ qua strongly connected
    //nên tạo ra một danh sách kề vô hướng mới
    int **matrix = listToMatrix(list, n);
    matrix = convertToUndirected(matrix, n);
    NODE **undirected = matrixToList(matrix, n);

    int *visited = new int[n]{0};

    queue<int> q;
    q.push(0);

    //Danh sách kề tạm lưu các đỉnh trong một thành phần liên thông
    NODE **component = new NODE *[n]
    { 0 };
    int count = 1;
    int tree = 0;

    while (q.size() > 0)
    {
        int curr = q.front();
        visited[curr] = 1;

        //Đếm cây thì dùng danh sách kề cũ để có thể đếm cây có hướng
        component[curr] = list[curr];
        q.pop();

        //Cho các đỉnh chưa duyệt vào stack
        NODE *move = undirected[curr];
        while (move != nullptr)
        {
            if (visited[move->vertex] == 0)
                q.push(move->vertex);
            move = move->adjacent;
        }

        //Dò tìm các đỉnh chưa duyệt (khi đồ thị chínhcó hơn 1 thành phần liên thông)
        if (q.size() == 0)
        {
            //Kết hợp kiểm tra thành phần liên thông trước có phải là cây
            if (directed)
                tree += isDirectedTree(component, n);
            else
                tree += isUndirectedTree(component, n);
            delete component;
            component = new NODE *[n]
            { 0 };

            for (int i = 0; i < n; i++)
            {
                if (visited[i] == 0)
                {
                    q.push(i);
                    count += 1;
                    break;
                }
            }
        }
    }
    
    // cout << "Total Trees: " << tree << endl;
    // cout << "Number of connected components: " << count << endl;
    return count;
}

int **copyMatrix(int **matrix, int n)
{
    int **copy = new int *[n];
    for (int i = 0; i < n; i++)
    {
        copy[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }

    return copy;
}

int **eraseVertex(int **matrix, int n, int vertex)
{
    int **copied = copyMatrix(matrix, n);
    for (int i = 0; i < n; i++)
    {
        copied[vertex][i] = 0;
        copied[i][vertex] = 0;
    }

    return copied;
}

int countCut(NODE **list, int n, bool directed)
{
    int count = 0;
    int component = countConnectedComponents(list, n, directed);
    int **matrix = listToMatrix(list, n);

    for (int i = 0; i < n; i++)
    {
        //Tạo một ma trận mới với đỉnh i bị xóa
        int **erased = eraseVertex(matrix, n, i);
        list = matrixToList(erased, n);

        //Đếm thành phần liên thông
        int new_comp = countConnectedComponents(list, n, directed);

        // cout << "Delete vertex " << i << " will make graph has: "
        // << new_comp << " connected component" << endl;

        //Do xóa đỉnh bằng cách biến nó thành đỉnh cô lập
        //Nên số thành phần liên thông phải trừ hao đi 1
        if (new_comp > component + 1)
        {
            cout << i << " is cut vertex" << endl;
            count += 1;
        }
    }

    cout << "Total of cut vertices: " << count << endl;
    return count;
}

int countBrigde(NODE **list, int n, bool directed)
{
    int count = 0;
    int component = countConnectedComponents(list, n, directed);
    int **matrix = listToMatrix(list, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                //Xóa cạnh
                matrix[i][j] = 0;
                if (!directed)
                    matrix[j][i] = 0;
                list = matrixToList(matrix, n);

                //Đếm thành phần liên thông
                int new_comp = countConnectedComponents(list, n, directed);

                // cout << "Delete (" << i << "-" << j << ") will make graph has "
                //<< new_comp << " connected components" << endl;

                //Nếu tăng thành phần liên thông thì là cạnh cầu
                if (new_comp > component)
                {
                    cout << "(" << i << "-" << j << ") is brigde edge" << endl;
                    count += 1;
                }

                //Hồi phục cạnh
                matrix[i][j] = 1;
                if (!directed)
                    matrix[j][i] = 1;
            }
        }
    }

    cout << "Total of bridge edges: " << count << endl;
    return count;
}

//Tạo đồ thị vô hướng từ đồ thị có hướng
int **convertToUndirected(int **matrix, int n)
{
    int **undirected = new int *[n];
    for (int i = 0; i < n; i++)
    {
        undirected[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
                undirected[i][j] = undirected[j][i] = 1;
        }
    }

    return undirected;
}

//Có thể dùng cho cả có hướng
int **complementGraph(int **matrix, int n, bool directed)
{
    int **complement = new int *[n];
    for (int i = 0; i < n; i++)
    {
        complement[i] = new int[n]{0};
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;

            if (matrix[i][j] == 0)
            {
                //Nếu là đồ thị có hướng thì cần 2 điều kiện sau
                //ĐK 1: đồ thị bù tại phải chưa được bật thành 1
                //Nếu bật nữa thì sẽ thành đối xứng

                //ĐK 2: vị trí đối xứng trong MT chính phải chưa bật
                //Vì cạnh đó đã tồn tại, không thể có trong MT bù

                if (complement[i][j] == 0 && matrix[j][i] == 0)
                {
                    //Thỏa thì bật ở vị trí đối xứng
                    complement[j][i] = 1;

                    //Nếu là vô hướng thì bật cả hai chỗ
                    if (!directed)
                        complement[i][j] = 1;
                }
            }
        }
    }

    return complement;
}

//Chỉ dùng cho có hướng
int **converseGraph(int **matrix, int n)
{
    int **converse = new int *[n];
    for (int i = 0; i < n; i++)
    {
        converse[i] = new int[n]{0};
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //Đảo chiều của cạnh
            if (matrix[i][j] == 1)
            {
                converse[j][i] = 1;
            }
        }
    }

    return converse;
}