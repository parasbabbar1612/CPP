#include<thread>
#include<mutex>
#include<iostream>
#include<vector>
#include<shared_mutex>

using namespace std;

class shared_example {
	shared_mutex sm;
	int val;
	
public:
	shared_example() :val(0) {};
	void increment() {
		unique_lock lock(sm);
		//Similar to unique_lock<shared_mutex> lock(sm);	
		++val;
	}
	int read() {
		shared_lock sl(sm);
		// Similar to shared_lock<shared_mutex> sl;
		return val;
	}
};

void shrd_mtx_ex() {
	shared_timed_mutex stm;
	if (stm.try_lock_shared()) {
		cout << "R+" << endl;
	}
	else {
		cout << "R-" << endl;
	}
	if (stm.try_lock_shared()) {
		cout << "R+" << endl;
	}
	else {
		cout << "R-" << endl;
	}
	if (stm.try_lock()) {
		cout << "W+" << endl;
	}
	else {
		cout << "W-" << endl;
	}
	stm.unlock_shared();
	stm.unlock_shared();
	if (stm.try_lock()) {
		cout << "W+" << endl;
	}
	else {
		cout << "W-" << endl;
	}
	if (stm.try_lock_shared()) {
		cout << "R+" << endl;
	}
	else {
		cout << "R-" << endl;
	}
}

int main() {
	shared_example se;
	auto inc_print = [&se] {
		for (int i = 0; i < 3; i++) {
			se.increment();
			mutex print_m;
			unique_lock pm(print_m);
			cout << "current value is: " << se.read() << endl;
		}
	};
	thread t1(inc_print);
	thread t2(inc_print);
	t1.join();
	t2.join();
	t1 = thread(shrd_mtx_ex);
	t1.join();
	return 0;
}