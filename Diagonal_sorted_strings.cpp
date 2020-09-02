#include<iostream>
#include<vector>
#include<map>

using namespace std;

vector<int> diagonals(vector<vector<char>> strings) {
    multimap<string, int> all_strings;
    int diagonal_no = 1;
    int dimensions = strings.size();
    for (int i = dimensions - 1; i >= 0; i--) {
        int r = i;
        int c = 0;
        string temp = "";
        int len = 0;
        while (len< dimensions) {
            while (r < dimensions && c < dimensions)
            {
                temp += strings[r][c];
                ++r;
                ++c;
                ++len;
                if (len == dimensions) break;
            }
            r = i;
            c = 0;
        }
        all_strings.insert({ temp,diagonal_no++ });
    }
    for (int i = 1; i < dimensions; i++) {
        int r = 0;
        int c = i;
        string temp = "";
        int len = 0;
        while (len < dimensions) {
            while (r < dimensions && c < dimensions) {
                temp += strings[r][c];
                ++r;
                ++c;
                ++len;
                if (len == dimensions) break;
            }
            r = 0;
            c = i;
        }
        all_strings.insert({ temp,diagonal_no++ });
    }
    vector<int> answer;
    for (auto i : all_strings) {
        answer.push_back(i.second);
    }
    return answer;
}
   
int main() {
    vector<vector<char>> strings = {{'a','c','a','b','b'},{'c','b','a','c','b'},{'a','a','e','c','b' },{'b','b','d','a','g'},{'a','b','e','b','a'}};
    vector<int> temp_answer = diagonals(strings);
    for (auto i : temp_answer) cout << i << " ";
	return 0;
}