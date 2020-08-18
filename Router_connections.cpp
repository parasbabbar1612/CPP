#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>

using namespace std;

class comp {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        return a[2] > b[2];
    }
};
 vector<vector<int>> minimumCost(int N, vector<vector<int>>& connections) {
      vector<bool> visited(N + 1, false);
      vector<vector<vector<int>>> graph(N + 1, vector<vector<int>>());
      priority_queue<vector<int>, vector<vector<int>>, comp> min_heap;
        for (auto i : connections) {
            graph[i[0]].push_back({i[0], i[1],i[2]});
            graph[i[1]].push_back({i[1],i[0],i[2]});
        }
        for (auto i : graph[1]) {
            min_heap.push(i);
        }
        visited[1] = true;
        vector<vector<int>> answer;
        while (!min_heap.empty()) {
            vector<int> cur_node = min_heap.top();
            min_heap.pop();
            if (visited[cur_node[1]]) continue;
            answer.push_back(cur_node);
            visited[cur_node[1]] = true;
            for (auto i : graph[cur_node[1]]) {
                if (!visited[i[1]]) min_heap.push(i);
            }
        }
        for (int i = 1; i < visited.size(); i++) if (!visited[i]) return {};
        return answer;
  }

int main() {
    vector<vector<int>> connections{ {1,2,1},{2,3,4},{3,4,6},{4,5,5},{3,5,1} };
    vector<vector<int>> answer = minimumCost(connections.size(), connections);
    for (auto i : answer) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}