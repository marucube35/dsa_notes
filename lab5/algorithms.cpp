#include "header.h"
void DFS(NODE **list, int n)
{
    int *visited = new int[n]{0};
    stack<int> s;
    s.push(0);
    int prev;

    while (s.size() > 0)
    {
        int curr = s.top();
        if (visited[curr] == 0)
        {
            cout << curr << "  ";
            visited[curr] = 1;
        }
        prev = curr;

        NODE *move = list[curr];
        while (move != nullptr)
        {
            if (visited[move->vertex] == 0)
            {
                s.push(move->vertex);
                break;
            }
            move = move->adjacent;
        }
        // Không có sự thay đổi stack (bắt đầu quay lui)
        if (prev == s.top())
        {
            s.pop();
        }
    }
    cout << endl;
}

void spanningDFS(NODE **list, int n)
{
    int *visited = new int[n]{0};
    int *in_spanning = new int[n]{0};
    NODE **spanningTree = new NODE *[n]
    { 0 };
    stack<int> s;
    s.push(0);
    int prev;

    while (s.size() > 0)
    {
        int curr = s.top();
        if (visited[curr] == 0)
        {
            cout << curr << "  ";
            visited[curr] = 1;
        }
        prev = curr;

        NODE *move = list[curr];
        while (move != nullptr)
        {
            if (visited[move->vertex] == 0)
            {
                s.push(move->vertex);
                
                NODE *node = createNODE(move->vertex);
                addTail(spanningTree[curr], node);

                NODE *node2 = createNODE(curr);
                addTail(spanningTree[node->vertex], node2);

                break;
            }
            move = move->adjacent;
        }
        // Không có sự thay đổi stack (bắt đầu quay lui)
        if (prev == s.top())
        {
            s.pop();
        }
    }
    cout << endl;
    printList(spanningTree, n);
}

void BFS(NODE** list, int n)
{
    int *visited = new int[n]{0};
    queue<int> q;
    q.push(0);

    while(q.size() > 0)
    {
        int curr = q.front();
        if(visited[curr]!= 0)
        {
            cout << curr<<" ";
            visited[curr] = 1;
        }

        NODE* move =list[curr];
        while(move!=nullptr)
        {
            if(visited[move->vertex]!=0)
                q.push(move->vertex);
            move = move->adjacent;
        }
    }
}
