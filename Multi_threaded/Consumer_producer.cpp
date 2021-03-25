#include<thread>
#include<iostream>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std;

condition_variable cv;
mutex consume_m;

int cargo = 0;

bool cargo_left() {
	return cargo != 0;
}

void consume() {
	unique_lock ul(consume_m);
	cv.wait(ul, cargo_left);
	cout << "Amount consumed by thread: " <<this_thread::get_id()<< " = " << cargo << endl;
	cargo = 0;
}

void produce() {
	for (int i = 0; i < 10; i++) {
		while (cargo_left()) {
			this_thread::yield();
		}
		unique_lock ul(consume_m);
		cargo = i + 1;
		cv.notify_one();
	}
}

int main() {
	vector<thread> all_threads;
	for (int i = 1; i <= 10; i++) {
		all_threads.push_back(thread(consume));
	}
	produce();
	for (auto& i : all_threads) {
		i.join();
	}
	return 0;
}