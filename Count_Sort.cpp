#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void count_sort(vector<int>& nums) {
    int max_num = INT_MIN;
    for (auto i : nums) {
        max_num = max(max_num, i);
    }
    vector<int> extra(max_num + 1);
    for (auto i : nums) {
        extra[i]++;
    }
    int k = 0;
    for (int i = 0; i < extra.size(); i++) {
        if (extra[i]) {
            for (int j = 0; j < extra[i]; j++)
                nums[k++]=i;
        }
    }
    extra.clear();
}

int main() {
    vector<int> nums{8,7,6,5,4};
    count_sort(nums);
    for (auto i : nums) {
        cout << i<<" ";
    }
    return 0;
}