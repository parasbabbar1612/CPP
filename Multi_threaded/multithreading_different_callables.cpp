#include<iostream>
#include<thread>
#include<vector>
#include<chrono>

using namespace std;

class test_c {
public:
	test_c() {};
	void check_larger(const int& a, const int& b) {
		int larger = a > b ? a : b;
		cout << larger << " Using member function ";
	}
};

class Comp {
public:
	void operator()(const int& a, const int& b) const{
		int larger = a > b ? a : b;
		cout << larger << " Using comparator ";
	}
};

void check_large(const int& a, const int& b) {
	int larger = a > b ? a : b;
	cout << larger << " Using main thread  ";
}

int main() {
	Comp c1;
	int a = 10, b = 11;
	test_c obj;
	check_large(a, b);
	thread t1{ c1,10,11 };
	thread t2{ [](const int& a,const int& b) {int larger = a > b ? a : b;cout << larger << " Using lambda "; },10,11 };
	thread t3(&test_c::check_larger, ref(obj), a, b);
	cout << "Waiting for threads to finish....." << endl;
	this_thread::sleep_for(chrono::seconds(5));
	t1.join();
	t2.join();
	t3.join();
	return 0;
}