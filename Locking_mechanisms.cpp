#include<thread>
#include<mutex>
#include<iostream>

using namespace std;

mutex global_lock;


void scoped_lock_global() {
	scoped_lock lock(global_lock);
	cout << "Scoped Lock is acquired by: " << this_thread::get_id()<<endl;
	for (int i = 0; i < 3; i++) {
		cout << i<<" ";
	}
	cout << endl;
}

void lock_global() {
	global_lock.lock();
	cout << "Basic lock acquired by: " << this_thread::get_id() << endl;
	for (int i = 0; i < 3; i++) {
		cout << i << " ";
	}
	cout << endl;
	global_lock.unlock();
}

void unique_lock_global() {
	unique_lock<mutex> unq_lock(global_lock);
	cout << "Unique lock is acquired by: " << this_thread::get_id() << endl;
	for (int i = 0; i < 3; i++) {
		cout << i << " ";
	}
	cout << endl;
}

void lock_guard_global() {
	lock_guard<mutex> lck_grd(global_lock);
	cout << "Lock guard is acquired by: " << this_thread::get_id() << endl;
	for (int i = 0; i < 3; i++) {
		cout << i << " ";
	}
	cout << endl;
}
int main() {
	thread t1(scoped_lock_global);
	thread t2(scoped_lock_global);
	scoped_lock_global();
	t1.join();
	t2.join();
	t1 = thread(lock_global);
	t2 = thread(lock_global);
	lock_global();
	t1.join();
	t2.join();
	t1 = thread(unique_lock_global);
	t2 = thread(unique_lock_global);
	unique_lock_global();
	t1.join();
	t2.join();
	t1 = thread(lock_guard_global);
	t2 = thread(lock_guard_global);
	lock_guard_global();
	t1.join();
	t2.join();
	return 0;
}