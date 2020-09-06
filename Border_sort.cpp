#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> spiral_seq(vector<vector<int>>& matrix) {
    vector<vector<int>> answer;
    int start_r = 0, start_c = 0;
    int rows = matrix.size(), cols = matrix[0].size();
    vector<int> temp;
    while (start_r < rows && start_c < cols) {
        int i = start_r;
        int j = start_c;
        while (start_r < rows && start_c < cols && j < cols) {
            temp.push_back(matrix[i][j]);
            ++j;
        }
        ++start_r;
        --j;
        ++i;
        while (start_r < rows && start_c < cols && i < rows) {
            temp.push_back(matrix[i][j]);
            ++i;
        }
        --i;
        --j;
        while (start_r < rows && start_c < cols && j >= start_c) {
            temp.push_back(matrix[i][j]);
            --j;
        }
        ++j;
        --i;
        ++start_c;
        while (start_r < rows && start_c < cols && i >= start_r) {
            temp.push_back(matrix[i][j]);
            --i;
        }
        --rows;
        --cols;
        sort(temp.begin(), temp.end());
        answer.push_back(temp);
        temp.clear();
    }
    return answer;
}

void convert(const vector<vector<int>>& spirals, vector<vector<int>>& matrix) {
    int counter = 0;
    int start_r = 0, start_c = 0;
    int rows = matrix.size(), cols = matrix[0].size();
    while (counter < spirals.size()) {
        int i = start_r;
        int j = start_c;
        int curr_c = 0;
        while (j < cols && curr_c<spirals[counter].size()){
            matrix[i][j]=spirals[counter][curr_c];
            ++curr_c;
            ++j;
        }
        ++start_r;
        --j;
        ++i;
        while (i < rows && curr_c < spirals[counter].size()) {
            matrix[i][j] = spirals[counter][curr_c];
            ++curr_c;
            ++i;
        }
        --i;
        --j;
        while (j >= start_c && curr_c < spirals[counter].size()) {
            matrix[i][j] = spirals[counter][curr_c];
            ++curr_c;
            --j;
        }
        ++j;
        --i;
        ++start_c;
        while (i >= start_r && curr_c < spirals[counter].size()) {
            matrix[i][j] = spirals[counter][curr_c];
            ++curr_c;
            --i;
        }
        --rows;
        --cols;
        ++counter;
    }
}

int main() {
    vector<vector<int>> matrix = {{9,7,4,5},{1,6,2,-6},{12,20,2,0},{-5,-6,7,-2}};
    if (!matrix.size()) return 0;
    convert(spiral_seq(matrix),matrix);
    for (auto i : matrix) {
        for (auto j : i) cout << j << " ";
        cout << endl;
    }
    return 0;
}