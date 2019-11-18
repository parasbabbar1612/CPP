#include<iostream>
#include <vector>

using namespace std;
int main()
{
	int n;
	cout << "\n Enter the side of square";
	cin >> n;
	vector<string> v1;
	string s1(n, '*');
	string s2 = "*";
	for (int i = 1; i < n - 1; i++) s2 += " ";
	s2 += "*";
	//cout << s1 << "\n" << s2;
	for (int i = 0; i < n; i++)
	{
		if (i == 0 || i == n - 1) v1.push_back(s1);
		else v1.push_back(s2);
	}
	for (int i = 0; i < n; i++) cout<<v1[i]<<"\n";
}