#include <iostream>
#include <vector>

using namespace std;

int sizeofbsequence(const vector<int>& nums)
{
	if (nums.size() < 2) return 0;
	int l = 0, r = 1;
	int max_len = INT_MIN;
	int len = 0;
	while (r < nums.size())
	{
		if (nums[l] != nums[r])
		{
			int seq_1 = nums[l];
			int seq_2 = nums[r];
			while (r < nums.size() && nums[l] == seq_1 && nums[r] == seq_2)
			{
				l = r + 1;
				r = l + 1;
				len += 2;
			}
			if (len > max_len) max_len = len;
			len = 0;
		}
		else
		{
			l = r;
			++r;
		}
	}
	return max_len;
}
int main()
{
	vector<int> v{ 0,1,0,1,1,0,1,0,1 };
	cout << sizeofbsequence(v);
	return 0;
