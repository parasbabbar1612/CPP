#include<iostream>
#include<list>

using namespace std;

bool m1(int a, int b)
{
	return a < b;
}
bool m2(int a, int b)
{
	return a > b;
}
bool m3(int a, int b)
{
	return a % 5 < b % 5;
}
int max(int a, int b, bool (*f) (int a, int b))
{
	return f(a, b) ? a : b;
}
int main()
{
	cout << max(4, 7, m2)<<endl;
	list<int> l1{ 3,5,7,2,9 };
	l1.sort([](int m, int n) {return m % 5 < n % 5;});
	for (auto i : l1) cout << i << " ";
	cout << endl;
	bool (*f) (int a, int b);
	f = m3;
	cout << f(6, 5) << endl;
	return 0;
}