#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>

using namespace std;

bool check_valid(pair<int,int> coordinates,map<pair<int, int>,pair<int, int>> &teleports,set<pair<int, int>> &blockers, vector<vector<bool>>& visited,int rows,int cols) {
    if (visited[coordinates.first][coordinates.second] || coordinates.first >= rows || coordinates.first >= cols || blockers.count(coordinates)) return false;
    if (coordinates.first == rows - 1 && coordinates.second == cols - 1) return true;
    if (teleports.find(coordinates) != teleports.end()) {
        return check_valid(teleports[coordinates], teleports, blockers, visited, rows, cols);
    }
    visited[coordinates.first][coordinates.second] = true;
    return check_valid({ coordinates.first,coordinates.second + 1 }, teleports, blockers, visited, rows, cols);
}

int main() {
    int n = 3;
    int m = 4;
    vector<vector<int>> teleports{ {0,1,1,1},{1,2,0,2},{0,3,2,1} };
    vector<vector<int>> obstacles{ {2,0},{1,0} };
    map<pair<int, int>, pair<int, int>> teleport_points;
    set<pair<int, int>> store_obstacles;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (auto i : teleports) {
        teleport_points[{i[0], i[1]}] = { i[2],i[3] };
    }
    for (auto i : obstacles) {
        store_obstacles.insert({ i[0],i[1] });
    }
    cout << check_valid({ 0,0 }, teleport_points,store_obstacles, visited, n, m);
}