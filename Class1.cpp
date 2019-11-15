#include<iostream>

using namespace std;
class first
{
private:
	int a, b, c;
public:
	int sum(int a, int b)
	{
		c = a + b;
		return c;
	}
	void show()
	{
		cout << c;
	}
};

int main()
{   
	first f ;
	f.sum(10,20);
	f.show();


}