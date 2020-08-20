#include<iostream>
#include<vector>

using namespace std;

void selection_sort(vector<int>& nums) {
    if (nums.size() <= 1) return;
    for (int i = 0; i < nums.size() - 1; i++) {
        int min_pos = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[min_pos]) {
                min_pos = j;
            }
        }
        if (min_pos != i) {
            int temp = nums[i];
            nums[i] = nums[min_pos];
            nums[min_pos] = temp;
        }
    }
}

int main() {
    vector<int> nums{5,3,2,1};
    selection_sort(nums);
    for (auto i : nums) {
        cout << i<<" ";
    }
    return 0;
}