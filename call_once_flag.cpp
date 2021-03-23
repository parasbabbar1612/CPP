#include<thread>
#include<iostream>
#include<vector>
#include<mutex>

using namespace std;

once_flag check_winner;

int winner;

void set_winner(int x) {
	winner = x;
}

void count(const int &id) {
	for (int i = 0; i < 1000; i++) {
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	call_once(check_winner,set_winner,id);
}

int main() {
	vector<thread> all_threads;
	for (int i = 1; i <= 10; i++) {
		all_threads.push_back(thread(count, i));
	}
	for (auto& i : all_threads) {
		i.join();
	}
	cout << "Winning thread is: " << winner << endl;
	return 0;
}