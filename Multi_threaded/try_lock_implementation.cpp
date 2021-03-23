#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>
#include<unordered_map>

using namespace std;

unordered_map<string, string> content;

mutex m;

void thread_caller(string url) {
	while (true) {
		if (m.try_lock()) {
			cout << "Thread with mutex currently is :" << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
			content[url] = "Content";
			m.unlock();
			break;
		}
		else {
			cout << "Thread with id: " << this_thread::get_id() << "tried to acquire mutex but it's locked" << endl;
			cout << "Peforming other opearations..." << endl;
		}
	}
}

int main() {
	thread t1(thread_caller,"thread1.com");
	thread t2(thread_caller, "thread2.com");
	t1.join();
	t2.join();
	for (auto i : content) {
		cout << i.first << " " << i.second << endl;
	}
	return 0;
}