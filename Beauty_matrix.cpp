#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
class comp_pq {
public:
    bool operator()(const int& a, const int& b) const {
        return a > b;
    }
};
class comp {
public:
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        priority_queue<int, vector<int>, comp_pq> min_heap;
        int beauty1, beauty2;
        for (auto i : a) min_heap.push(i);
        int check = -1;
        while (!min_heap.empty()) {
            if (check == -1) {
                check = min_heap.top() + 1;
                min_heap.pop();
            }
            else if (min_heap.top() == check) {
                check = min_heap.top() + 1;
                min_heap.pop();
            }
            else if (min_heap.top() != check) {
                beauty1 = check;
                break;
            }
        }
        if (min_heap.empty()) beauty1 = check;
        min_heap = priority_queue<int,vector<int>,comp_pq>();
        for (auto i : b) min_heap.push(i);
        check = -1;
        while (!min_heap.empty()) {
            if (check == -1) {
                check = min_heap.top() + 1;
                min_heap.pop();
            }
            else if (min_heap.top() == check) {
                check = min_heap.top() + 1;
                min_heap.pop();
            }
            else if (min_heap.top() != check) {
                beauty2 = check;
                break;
            }
        }
        if (min_heap.empty()) beauty2 = check;
        return beauty1 < beauty2;
    }
};

vector<vector<int>> beauty(vector<vector<int>>& nums,int factor) {
    int i = 0, j = 0;
    vector<vector<int>> temp_vector;
    while (i < nums.size()) {
        while (j < nums.size()) {
            vector<int> temp;
            for (int k = i; k < i + factor; k++) {
                for (int l = j; l < j + factor; l++) {
                    temp.push_back(nums[k][l]);
                }
            }
            temp_vector.push_back(temp);
            j += factor;
        }
        i += factor;
        j = 0;
    }
    comp c1;
    sort(temp_vector.begin(), temp_vector.end(), c1);
    return temp_vector;
}

int main() {
    int factor = 2;
    vector<vector<int>> nums{ {2,3,4,5},{1,4,5,6},{6,9,10,12},{4,6,7,8} };
    vector<vector<int>> temp = beauty(nums, factor);
    vector<vector<int>> answer(nums.size(), vector<int>(nums.size()));
    int i = 0, j = 0;
    int row = 0, col = 0;
    while (i < nums.size()) {
        while (j < nums.size()) {
            for (int k = i; k < i + factor; k++) {
                for (int l = j; l < j + factor; l++) {
                    answer[k][l] = temp[row][col++];
                    if (col == nums.size()) {
                        ++row;
                        col = 0;
                    }
                }
            }
            j += factor;
        }
        i += factor;
        j = 0;
    }
    for (auto i : answer) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}