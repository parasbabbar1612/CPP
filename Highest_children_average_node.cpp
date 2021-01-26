#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

class Node {
public:
	int val;
	vector<Node*> children;
	Node(int value, vector<Node*> this_children) :val(value), children(this_children) {};
	Node(int value) :val(value) {};
};

float dfs(Node* busiest, unordered_map<Node*, pair<float,float>>& count) {
	if (!busiest->children.size()) {
		count[busiest].first += busiest->val;
		count[busiest].second++;
		return 1;
	}
	for (auto i : busiest->children) {
		count[busiest].second += dfs(i, count);
		count[busiest].first += count[i].first;
	}
	count[busiest].first += busiest->val;
	count[busiest].second++;
	return count[busiest].second;
}

Node* getBusiestNode(Node* root) {
	if (!root) return nullptr;
	unordered_map<Node*, pair<float,float>> count;
	dfs(root, count);
	Node* max_n = nullptr;
	float max_val = FLT_MIN;
	for (auto i : count) {
		if (i.second.second > 1) {
			float temp_val = i.second.first / i.second.second;
			cout << i.first->val << " " << temp_val << endl;
			if (temp_val > max_val) {
				max_val = temp_val;
				max_n = i.first;
			}
		}
	}
	return max_n;
}
int main() {
	Node* n1 = new Node(20);
	Node* n2 = new Node(12);
	Node* n3 = new Node(18);
	Node* n4 = new Node(11);
	Node* n5 = new Node(2);
	Node* n6 = new Node(3);
	Node* n7 = new Node(15);
	Node* n8 = new Node(8);
	vector<Node*> v1{ n2,n3 };
	vector<Node*> v3{ n7,n8};
	vector<Node*> v2{ n4,n5,n6 };
	n1->children = v1;
	n2->children = v2;
	n3->children = v3;
	Node* answer = getBusiestNode(n1);
	cout << n1->val;
	return 0;
}