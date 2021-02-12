#include<iostream>
#include<thread>
#include<vector>

using namespace std;

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
	check_large(a, b);
	thread t1{ c1,10,11 };
	thread t2{ [](const int& a,const int& b) {int larger = a > b ? a : b;cout << larger << " Using lambda "; },10,11 };
	t1.join();
	t2.join();
	return 0;
}