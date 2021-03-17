#include<thread>
#include<mutex>
#include<iostream>

using namespace std;

class thread_guard {
	thread& raii_thread;
public:
	thread_guard(thread &new_thread):raii_thread(new_thread){}
	~thread_guard() {
		if (raii_thread.joinable()) {
			raii_thread.join();
		}
	}
};

struct my_func {
	void operator()() {
		cout << "Thread being implemented using RAII : " << this_thread::get_id();
		for (int i = 0; i < 10; i++) {
			cout << i << endl;
		}
	}
};

int main() {
	my_func obj;
	thread t1(obj);
	thread_guard wrapper(t1);
	return 0;
}