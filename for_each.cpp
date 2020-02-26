#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

int main()
{
	list<int> l1{ 2,5,1,7,3,2,9,6 };
	list<int> l2;
	for_each(l1.begin(), l1.end(), [&l2,&l1](int i) {if (i % 2 == 0) l2.push_back(i); });;
	for (auto j : l2) cout << j << " ";
	return 0;
}