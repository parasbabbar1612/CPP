#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>

using namespace std;

mutex thread_lock;
int tasks = 0;
void check_usage(int id) {
	int thread_check = 0;
	while (tasks < 10) {
		unique_lock<mutex> new_lock(thread_lock);
		if(id == tasks % 2 && tasks < 10) {
			tasks++;
		}
		else thread_check++;
	}
	cout << "Thread with id : " << id << " checked for it's turn " << thread_check << " times" << endl;
}

int main() {
	vector<thread> all_threads(2);
	for (int i = 0; i <2; i++) {
		all_threads[i] = thread(check_usage, i);
	}
	for (auto& i : all_threads) i.join();
	return 0;
}