#include <iostream>
#include <conio.h>
using namespace std;

int findsum(int x)
{
	int a;
	int sum = 0;
	if ((x/10)==0) return x;
	if (x < 0) x = -(x);
	while(x>0)
	{
		a = x % 10;
	    sum += a;
	    x /= 10;
	}
	x = sum;
	if ((x / 10) == 0) return x;
	else findsum(x);
}
int main()
{
	int num ;
	cout << "\n Enter input";
	cin >> num;
	cout << findsum(num);
}