#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	int n,temp;
	int a[] = { 0,1,2,3,4,5,6};
	n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n/2 ; i++)
	{
		temp = a[i];
		a[i] = a[n-i-1];
		a[n-i-1] = temp;
	}
	for (int j = 0; j < n; j++) cout << a[j];
}