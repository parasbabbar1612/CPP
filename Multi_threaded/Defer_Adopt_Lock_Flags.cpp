#include<thread>
#include<mutex>
#include<iostream>

using namespace std;

struct bank_account {
	int balance;
	explicit bank_account(const int& balance) :balance(balance) {};
	mutex m1;
};

void transfer_amount(bank_account& from, bank_account& to,const int &amount) {
	if (&from == &to) return;
	lock(from.m1, to.m1);
	unique_lock<mutex> ul1(from.m1, adopt_lock);
	unique_lock<mutex> ul2(to.m1, adopt_lock);
	
	//Similar approach
	//unique_lock<mutex> ul1(from.m1, defer_lock);
	//unique_lock<mutex> ul2(to.m1, defer_lock);
	//lock(ul1, ul2);
	
	//Another approach
	//scoped_lock sl(from.m1, to.m1);
	
	from.balance -= amount;
	to.balance += amount;
}

mutex ownership;

void check_ownership() {
	unique_lock<mutex> ul(ownership, try_to_lock);
	
	//Similar to second if statement
	//if (ul) cout << "*";
	
	if (ul.owns_lock()) cout << "*";
	else cout << "x";
}

int main() {
	bank_account acc1(100);
	bank_account acc2(100);
	int amount1 = 50, amount2 = 70;;
	thread t1(transfer_amount, ref(acc1), ref(acc2), ref(amount1));
	thread t2(transfer_amount, ref(acc2), ref(acc1), ref(amount2));
	t1.join();
	t2.join();
	cout << "Account holder1 balance= " << acc1.balance<<endl;
	cout << "Account holder2 balance= " << acc2.balance<<endl;
	vector<thread> all_thread;
	for (int i = 0; i < 100; i++) {
		all_thread.push_back(thread(check_ownership));
	}
	for (auto& i : all_thread) {
		i.join();
	}
	return 0;
}