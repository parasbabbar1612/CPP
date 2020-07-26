#include<iostream>
#include<vector>

using namespace std;

void insertionsort(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		int j = i - 1;
		int val = arr[i];
		while (j >= 0 && arr[j] > val) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = val;
	}
}

int main()
{
	int n;
	cout << "Enter the size of the array" << endl;
	cin >> n;
	if (n<1) return 0;
	vector<int> arr(n);
	cout << "Enter elments of the array" << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	insertionsort(arr);
	cout << "Array after sorting" << endl;
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}