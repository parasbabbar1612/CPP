#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<queue>

class comp {
public:
	bool operator()(const int& a, const int& b) const {
		return a > b;
	}
};
using namespace std;

int max_min(vector<int> &nums,int k)
{
	if (k > nums.size()) k = nums.size();
	priority_queue<int,vector<int>,comp> min_heap;
	unordered_map<int, int> check;
	for (int i = 0; i < k-1; i++) {
		min_heap.push(nums[i]);
		check[nums[i]] = i;
	}
	int max_num = INT_MIN;
	int start = 0;
	int end = k-1;
	while (end < nums.size()) {
		min_heap.push(nums[end]);
		check[nums[end]] = end;
		int curr_min;
		if (min_heap.top() == nums[start]) {
			curr_min = min_heap.top();
			min_heap.pop();
		}
		else if (check[min_heap.top()] < start) {
			while (check[min_heap.top()] < start) min_heap.pop();
			curr_min = min_heap.top();
		}
		max_num = max(max_num, curr_min);
		++start;
		++end;
	}
	return max_num;
}
int main() {
	vector<int> ques{1,2,3,4,5};
	cout << max_min(ques, 3);
	return 0;
}