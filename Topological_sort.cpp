#include<iostream>
#include<unordered_map>
#include<vector>
#include<unordered_set>

using namespace std;

void topological_sort(int node, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited, vector<int>& order) {
    if (!graph[node].size()) {
        order.push_back(node);
        return;
    }
    for (auto i : graph[node]) {
        if (!visited.count(i)) {
            visited.insert(i);
            topological_sort(i, graph, visited, order);
        }
    }
    order.push_back(node);
}

int main() {
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    vector<int> order;
    graph[1].push_back(3);
    graph[2].push_back(3);
    graph[2].push_back(4);
    graph[3].push_back(5);
    graph[4].push_back(6);
    graph[5].push_back(7);
    graph[5].push_back(6);
    graph[6].push_back(8);
    for (auto i : graph) {
        if (!visited.count(i.first)) {
            visited.insert(i.first);
            topological_sort(i.first, graph, visited, order);
        }
    }
    for (int i = order.size() - 1; i >= 0; i--) {
        cout << order[i] << " ";
    }
    return 0;
}