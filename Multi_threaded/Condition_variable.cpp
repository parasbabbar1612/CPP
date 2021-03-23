#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>

using namespace std;

mutex thread_lock;
int tasks = 0;
condition_variable check_threads;

void check_usage(int id) {
	int thread_check = 0;
	while (tasks < 10) {
		unique_lock<mutex> new_lock(thread_lock);
		while(id != tasks % 5 && tasks < 10) {
			++thread_check;
			check_threads.wait(new_lock);
		}
		if (tasks < 10) {
			++tasks;
			new_lock.unlock();
			check_threads.notify_all();
		}
	}
	cout << "Thread with id : " << id << " checked for it's turn " << thread_check << " times" << endl;
}

int main() {
	vector<thread> all_threads(5);
	for (int i = 0; i <5; i++) {
		all_threads[i] = thread(check_usage, i);
	}
	for (auto& i : all_threads) i.join();
	return 0;
}