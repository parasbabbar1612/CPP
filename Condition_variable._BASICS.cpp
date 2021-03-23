#include<thread>
#include<iostream>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std;

condition_variable cv;
mutex m1;

bool ready = false;

void race(const int &id) {
	unique_lock ul(m1);
	while (!ready) {
		cv.wait(ul);
	}
	cout << "Thread of exection: " << id << endl;
}

void start_race() {
	ready = true;
	cv.notify_all();
}

int main() {
	vector<thread> all_threads;
	for (int i = 1; i <= 10; i++) {
		all_threads.push_back(thread(race,i));
	}
	start_race();
	for (auto& i : all_threads) {
		i.join();
	}
	return 0;
}