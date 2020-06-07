#include<iostream>
#include<vector>
#include<queue>
#define vertex 6

using namespace std;

vector<int> visitedDFS(vertex);

void addedge(vector<pair<int,int>> g[],int v,int edge,int weight)
{
    g[v].push_back({edge,weight});
    g[edge].push_back({ v,weight });
}

void printgraph(vector<pair<int,int>> g[],int v)
{
    for (int i = 0; i < v; i++)
    {
        cout << "Vertex " << i << " ";
        for (auto j:g[i])
        {
            cout << " Edges with-> "<<j.first<<" Weight "<<j.second;
        }
        cout << endl;
    }
}

void BFS(vector<pair<int, int>> g[], int start,int vertices)
{
    queue<int> BFS;
    BFS.push(start);
    vector<int> visited(vertices);
    while (!BFS.empty())
    {
        int el = BFS.front();
        BFS.pop();
        cout << el<<" ";
        visited[el] = 1;
        for (auto i : g[el])
        {
            if (visited[i.first] == 0)
            {
                BFS.push(i.first);
                visited[i.first] = 1;
            }
        }
    }
}

void DFS(vector<pair<int, int>> g[], int start, int vertices)
{
    int el = start;
    visitedDFS[el] = 1;
    cout << el<<" ";
    for (auto i : g[el])
    {
        if (visitedDFS[i.first] == 0)
        {
            visitedDFS[i.first] = 1;
            DFS(g, i.first, vertex);
        }
    }

}

int main()
{
    vector<pair<int,int>> graph[vertex];
    addedge(graph, 0, 1,10);
    addedge(graph, 0, 2,5);
    addedge(graph, 1, 3,8);
    addedge(graph, 2, 3,10);
    addedge(graph, 3, 4,5);
    addedge(graph, 3, 5,6);
    printgraph(graph,vertex);
    cout << "BFS" << endl;
    BFS(graph, 0, 6);
    cout << endl;
    cout <<"DFS"<<endl;
    DFS(graph, 0, 6);
    return 0;
}