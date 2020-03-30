#include<iostream>
#include<memory>
#include<string>

using namespace std;

class test
{
public:
	int a, b, c;
	test() :a(0), b(0), c(0) {};
	test(int x, int y, int z) :a(x), b(y), c(z) {};
};

int main()
{
	unique_ptr<int> up = make_unique<int>(15);
	shared_ptr<double> sp = make_shared<double>(10.10);
	int* p = new int(5);
    weak_ptr<double> wp=sp;
	cout << *up<<endl;
	cout << *sp << endl;
	shared_ptr<double> sp1 = wp.lock();
	cout << *sp1<<endl;
	cout << sp1.use_count() << endl;
	sp=make_shared<double>(100.50);
	sp1.reset(new double(40.78));
	cout << *sp << endl;
	cout << *sp1 << endl;
	cout << sp1.use_count() << endl;
	shared_ptr<test> st = make_shared<test>(1, 2, 3);
	cout << st->a << " " << st->b << " " << st->c << endl;
	if (wp.expired()) cout << "Object deleted" << endl;
	else cout << "Not deleted" << endl;
	int* p1 = new int(10);
	shared_ptr<int> sr(p1);
	sr.reset(new int(40));
	cout << *sr << endl;
	cout << boolalpha << sr.unique() << endl;
	cout << noboolalpha << sr.unique() << endl;
	unique_ptr<int> sw1 = make_unique<int>(50);
	unique_ptr<int> sw2 = make_unique<int>(60);
	swap(sw1,sw2);
	cout << *sw1 << " " << *sw2 << endl;
	shared_ptr<int> sw3 = make_unique<int>(50);
	shared_ptr<int> sw4 = make_unique<int>(60);
	sw3.swap(sw4);
	cout << *sw3 << " " << *sw4 << endl;
	int* p2 = new int(50);
	if (sw4.get() == p2) cout << "sw4 and p2 point to same memory address"<< endl;
	else cout << "sw4 and p2 don't point to same memory address" << endl;
	shared_ptr<int> sp5(p2);
	if (sp5.get() == p2) cout << "sp5 and p2 point to same memory address" << endl;
	else cout << "sp5 and p2 don't point to same memory address" << endl;
	sp5.reset();
	return 0;
}