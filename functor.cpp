#include<iostream>
#include<list>
#include<functional>
#include<map>

using namespace std;

class test1
{
public:
	int a, b, c;
	test1():a(0),b(0),c(0){}
	test1(int x,int y,int z):a(x),b(y),c(z){}
	int getvol() const { return a * b * c; }
	bool operator<(const test1& ob1) const { return getvol() < ob1.getvol(); }
};
class myfunc
{
public:
bool operator()(int a,int b)
{
	return a > b;
}
bool operator()(const test1& ob1, const test1& ob2) const
{
	return ob1.getvol() > ob2.getvol();
}
};
test1 min(const test1 &a, const test1 &b, function<bool(const test1 ,const test1)> F)
{
	return F(a, b) ? a : b;
}

template <class T> int min2(int a, int b, T f)
{
	return f(a, b) ? a : b;
}
ostream& operator<<(ostream& str, const test1& t1)
{
	str <<"["<< t1.a << " " << t1.b << " " << t1.c<<"]";
	return str;
}
int main()
{
	myfunc f1;
	test1 ob1(5, 10, 16);
	test1 ob2(10, 10, 10);
	cout << min(ob1,ob2,f1)<<endl;
	cout << min2(5, 10, f1)<<endl;
	list<int> l1{ 3,1,4,7,2,5 };
	l1.sort([](int a, int b) {return a < b; });
	for (auto i : l1) cout << i << " ";
	cout << endl;
	l1.sort(f1);
	for (auto i : l1) cout << i << " ";
	cout << endl;
	map<test1, int, myfunc> m1{ {ob1,100},{ob2,200} };
	for (auto i : m1) cout << i.first << " " << i.second << endl;
	return 0;
}