#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class produce_consume{
private:
	mutex lock_data;
	condition_variable check_data;
	queue<int> data_packets;
public:
	void send_data(int curr) {
		unique_lock<mutex> dl(lock_data);
		data_packets.push(curr);
		dl.unlock();
		check_data.notify_one();
	}
	int process_data() {
		unique_lock<mutex> dl(lock_data);
		while (data_packets.empty()) {
			check_data.wait(dl);
		}
		int curr = data_packets.front();
		data_packets.pop();
		return curr;
	}
};

produce_consume obj;

void send_data(int id) {
	cout << "Thread " << id << " is transmitting data...." << endl;
	for (int i = 0; i < 1000; i++) {
		obj.send_data(i);
	}
	obj.send_data(-1);
	cout << "Finished transmitting data.." << endl;
}

void process_data(int id) {
	cout << "Thread " << id << " has started processing data" << endl;
	int processed = 0;
	while (true) {
		int curr = obj.process_data();
		if (curr > -1) ++processed;
		else {
			obj.send_data(-1);
			break;
		}
	}
	cout << "Items processed by thread " << id << " is =" << processed << endl;
}
int main() {
	thread sender(send_data, 1);
	thread process1(process_data, 2);
	thread process2(process_data, 3);
	sender.join();
	process1.join();
	process2.join();
	return 0;
}