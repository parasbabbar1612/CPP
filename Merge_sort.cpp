#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& nums, int low, int mid, int high) {
    vector<int> extra;
    int i = low;
    int j = mid + 1;
    while (i <= mid && j <= high) {
        if (nums[i] < nums[j]) {
            extra.push_back(nums[i++]);
        }
        else if (nums[i] > nums[j]) {
            extra.push_back(nums[j++]);
        }
        else {
            extra.push_back(nums[i++]);
            extra.push_back(nums[j++]);
        }
    }
    for (; i <= mid; i++) {
        extra.push_back(nums[i]);
    }
    for (; j <= high; j++) {
        extra.push_back(nums[j]);
    }
    for (int k = 0; k < extra.size(); k++) {
        nums[low + k] = extra[k];
    }
}

void merge_sort(vector<int>& nums,int low,int high) {
    if (low < high) {
        int mid = (low+high) / 2;
        merge_sort(nums, low, mid);
        merge_sort(nums, mid+1, high);
        merge(nums, low, mid, high);
    }
}

int main() {
    vector<int> nums{5,4,3,2,1};
    merge_sort(nums,0,nums.size()-1);
    for (auto i : nums) {
        cout << i<<" ";
    }
    return 0;
}