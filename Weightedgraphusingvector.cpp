#include<iostream>
#include<vector>

using namespace std;

void addedge(vector<pair<int,int>> g[],int vertex,int edge,int weight)
{
    g[vertex].push_back({edge,weight});
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

int main()
{
    const int vertices = 5;
    vector<pair<int,int>> graph[vertices];
    addedge(graph, 0, 1,10);
    addedge(graph, 0, 4,5);
    addedge(graph, 1, 2,8);
    addedge(graph, 1, 3,10);
    addedge(graph, 1, 4,5);
    addedge(graph, 2, 3,6);
    addedge(graph, 3, 1,8);
    addedge(graph, 3, 4,9);
    addedge(graph, 4, 1,5);
    printgraph(graph,vertices);
    return 0;
}