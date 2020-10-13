#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<chrono>

using namespace std;

class semaphore{
private:
	mutex lock_data;
	condition_variable check;
	int count;
public:
	semaphore(int num) :count(num) {};
	void acquire() {
		unique_lock<mutex> acq_lock(lock_data);
		while (!count) {
			check.wait(acq_lock);
		}
		--count;
		cout << "Lock acquired" << endl;
	}
	void release() {
		unique_lock<mutex> dl(lock_data);
		++count;
		dl.unlock();
		check.notify_one();
	}
};

semaphore obj(5);

void process_data(int id) {
	obj.acquire();
	cout << "Thread trying to acquire the lock is " << id << endl;
	cout << "Thread is being processed..."<<endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Thread processed!" << endl;
	obj.release();
}
int main() {
	vector<thread> all_threads(10);
	for (int i = 0; i < 10; i++) {
		all_threads[i] = thread(process_data, i);
	}
	for (auto& i : all_threads) i.join();
	return 0;
}