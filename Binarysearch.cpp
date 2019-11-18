#include<iostream>
#include <algorithm>

using namespace std;
bool findel(int arr[], int beg, int end, int x)
{
	bool ans;
	if (beg <= end)
	{
		int m = (beg + (end - 1)) / 2;
		if (x == arr[m]) return true;
		else if (x < arr[m])  findel(arr, beg, m - 1, x);
		else  findel(arr, m + 1, end, x);
	}
	else return false;

}
int main()
{
	bool answer;
	int n, el;
	cout << "\n Enter n";
	cin >> n;
	int* a = new int[n];
	cout << "\n Enter array";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cout << "\n Enter number to be searched";
	cin >> el;
	sort(a, a + n);
	answer = findel(a, 0, n - 1, el);
	if (answer == true) cout << "\n Found";
	else cout << "\n Not found";
delete[] a;
}
