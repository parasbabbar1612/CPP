#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>

using namespace std;

void independent_execution() {
	cout << "Thread id is:" << this_thread::get_id()<<endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "Exiting independent thread" << endl;
}

void thread_caller() {
	cout << "Making independent thread.." << endl;
	thread t1(independent_execution);
	t1.detach();
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Independent thread detached" << endl;
}

int main() {
	thread_caller();
	this_thread::sleep_for(chrono::seconds(2));
	return 0;
}