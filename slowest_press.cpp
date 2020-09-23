#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
#include<string>

using namespace std;

char slowest(vector<vector<int>> key_times) {
    int start = 0;
    int max_time= INT_MIN;
    char answer;
    for (auto i : key_times) {
        int curr_time = i[1] - start;
        if (curr_time > max_time) {
            max_time = curr_time;
            answer = i[0] + 'a';
        }
        start = i[1];
    }
    return answer;
}
 int main() {
     vector<vector<int>> times{ {0, 1}, { 0,3 }, { 4,5 },{5,6},{4,10} };
     cout << slowest(times);
     return 0;
}