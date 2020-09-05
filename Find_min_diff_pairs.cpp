#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

void check(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    unordered_map<int, vector<pair<int, int>>> diff;
    int min_diff = INT_MAX;
    for (int i = 0; i < nums.size() - 1; i++) {
        min_diff = min(min_diff, abs(nums[i] - nums[i + 1]));
        diff[abs(nums[i] - nums[i + 1])].push_back({ nums[i],nums[i + 1] });
    }
    for (auto i : diff[min_diff]) {
        cout << i.first << " " << i.second << endl;
    }
}
int main() {
    vector<int> nums{4,-2,-1,3};
    check(nums);
    return 0;
}