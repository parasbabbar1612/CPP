#include<iostream>
#include<vector>

using namespace std;

void bubblesort(vector<int>& arr) {
	int flag ;
	for (int i = 0; i < arr.size() - 1; i++) {
		flag = 0;
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
				flag = 1;
			}
		}
		if (!flag) break;
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
	bubblesort(arr);
	cout << "Array after sorting" << endl;
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}