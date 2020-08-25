#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node() :next(nullptr) {};
	Node(int value) :data(value), next(nullptr) {};
};

class llist {
public:
	Node *head, *tail;
	llist() { head = tail = nullptr;}
	void add(int x);
	void del();
};

void llist :: add(int x)
{
	Node* new_node = new Node(x);
	if (!head && !tail) head = tail = new_node;
	else {
		tail->next = new_node;
		tail = new_node;
	}
}

void llist::del() {
	if (head == tail) delete head;
	else {
		Node* temp = head;
		while (temp) {
			head = head->next;
			delete temp;
			temp = head;
		}
	}
	head = tail = nullptr;
}

void radix_sort(vector<int>& nums, int max_val) {
	int divisor = 1;
	vector<llist*> helper;
	for (int i = 0; i < 10; i++) {
		llist* obj = new llist();
		helper.push_back(obj);
	}
	while (max_val>=divisor) {
		for (auto i : nums) {
			int temp = i / divisor;
			int idx = temp % 10;
			helper[idx]->add(i);
		}
		int pos = 0;
		for (auto i : helper) {
			if (i->head) {
				Node* track = i->head;
				while (track) {
					nums[pos++] = track->data;
					track = track->next;
				}
				i->del();
			}
		}
		divisor *= 10;
	}
}

int main() {
	vector<int> nums{ 1000,25,310,498,50};
	int max_val = INT_MIN;
	for (auto i : nums) max_val = max(max_val, i);
	if(nums.size()>1) radix_sort(nums, max_val);
	for (auto i : nums) cout << i << " ";
	return 0;
}