
#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
	int number;
	int a, b=0;
	cout << "\n Enter number";
	cin >> number;
		while (number != 0)
		{
			a = number % 2;
			b = (b * 10) + a;
			number /= 2;
	    }
		number = b;
		b = 0;
		while (number != 0)
		{
			a = number % 10;
			b = (b * 10) + a;
			number /= 10;
		}

		cout << b;
}