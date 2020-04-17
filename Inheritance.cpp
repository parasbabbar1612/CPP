#include<iostream>
#include<conio.h>

using namespace std;

class A
{
	int a1;
protected:
	int a2;
public:
	int a3;
	A() :a1(0), a2(0), a3(0) {};
};

class pc
{
	int pc1;
protected:
	int pc2;
public:
	int pc3;
	pc() :pc1(0), pc2(0), pc3(0) {};
};

class pvtc
{
	int pvt1;
protected:
	int pvt2;
public:
	int pvt3;
	pvtc() :pvt1(0), pvt2(0), pvt3(0) {};
};

class absc:public A
{
public:
	int absv;
	absc() :absv(0) {};
	absc(int x) :absv(x) {};
	virtual void mult1() = 0;
	virtual void mult2()
	{
		absv = absv * 10;
	}
};

class B :protected pc,private pvtc,public absc
{
	int b1;
protected:
	int b2;
public:
	int b3;
	B() :b1(0), b2(0), b3(0) {};
	void seta2()
	{
		a2 = 100;
		cout << a2 << endl;
	}
	void setpc()
	{
		pc2 = 1000;
		pc3 = 1001;
		cout << pc2 << " , " << pc3 << endl;
	}
	void setpvt()
	{
		pvt2 = 110;
		pvt3 = 111;
		cout << pvt2 << " , " << pvt3 << endl;
	}
	void mult1()
	{
		absv = 11;
		absv = 11 * 5;
	}
};

int main()
{
	absc* a1;
	B b;
	a1 = static_cast<absc*>(&b);
	a1->absv = 8;
	cout << b.absv<<endl;
	b.a3 = 10;
	cout << b.a3<<endl;
	b.seta2();
	b.setpc();
	b.setpvt();
	b.mult1();
	cout << b.absv << endl;
	b.mult2();
	cout << b.absv << endl;
	B* b1 = static_cast<B*>(a1);
	b1->a3 = 10;
	b1->absv = 5;
	cout << b.a3 << " " << b.absv << endl;
	return 0;
}