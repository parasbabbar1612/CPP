#include <vector>
#include <iostream>
#include<algorithm>

using namespace std;

class Comp {
public:
    bool operator()(const pair<int,int>& a, const pair<int, int>& b) const {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    }
};

vector<int> bouncingDiagonals(vector<vector<int>> matrix) {
    Comp c1;
    vector<int> answer;
    vector<pair<int,int>> all_pairs;
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        int r = i;
        int c = 0;
        int start_val = matrix[r][c];
        int sum = 0;
        while (r >= 0 && c < n) {
            sum += matrix[r][c];
            --r;
            ++c;
        }
        r += 2;
        while (r < n && c < n) {
            sum += matrix[r][c];
            ++r;
            ++c;
        }
        all_pairs.push_back({start_val,sum });
    }
    sort(all_pairs.begin(), all_pairs.end(), c1);
    for (auto i : all_pairs) {
        answer.push_back(i.first);
    }
    return answer;
}


int main() {
    //vector<vector<int>> matrix{ {1,3,2,5},{3,2,5,0},{9,0,1,3},{6,1,0,8}};
    vector<vector<int>> matrix{ { 2,3,2 }, { 0,2,5 },{1, 0, 1} };
    for (auto i : bouncingDiagonals(matrix)) cout << i << " ";
    return 0;

}