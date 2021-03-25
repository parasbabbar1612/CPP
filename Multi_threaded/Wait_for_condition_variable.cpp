#include<thread>
#include<iostream>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std;

condition_variable cv;

int value;

void read_val() {
	cin >> value;
	cv.notify_one();
}

int main() {
	thread t1(read_val);
	mutex m1;
	unique_lock ul(m1);
	while (cv.wait_for(ul, chrono::seconds(1)) == cv_status::timeout) {
		cout << "..";
	}
	cout << endl;
	cout << "Value entered :" << value<< endl;
	t1.join();
	return 0;
}