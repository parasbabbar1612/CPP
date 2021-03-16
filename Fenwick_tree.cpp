#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

class Fenwick {

private:
	vector<int> orignial_array;
	vector<int> fenwick_tree;
	
public:
	Fenwick() {};
	Fenwick(const vector<int>& original) {
		orignial_array = original;
		create_fenwick_tree();
	}
	int invert_bits(int num);
	int calc_next(const int& index);
	int calc_parent(const int& index);
	void create_fenwick_tree();
	int prefix_sum(const int& range); 
	int find_range_sum(const int& i, const int& j);
	void update_element(const int& index, const int& value);
};

int Fenwick::invert_bits(int num) {
	int x = log2(num) + 1;
	for (int i = 0; i < x; i++)
		num = (num ^ (1 << i));
	return num;
}

int Fenwick::calc_next(const int& index) {
	int answer=invert_bits(index);
	++answer;
	answer &= index;
	return answer + index;
}

int Fenwick::calc_parent(const int& index) {
	int answer = invert_bits(index);
	++answer;
	answer &= index;
	return index - answer;
}

void Fenwick::create_fenwick_tree() {
	int size = orignial_array.size();
	fenwick_tree.resize(size + 1);
	for (int i = 0; i < size; i++) {
		int curr_index = i + 1;
		while (curr_index < size + 1) {
			fenwick_tree[curr_index] += orignial_array[i];
			curr_index = calc_next(curr_index);
		}
	}
}

int Fenwick::prefix_sum(const int& range) {
	int sum = 0;
	int curr_index = range + 1;
	while (curr_index > 0) {
		sum += fenwick_tree[curr_index];
		curr_index = calc_parent(curr_index);
	}
	return sum;
}

int Fenwick::find_range_sum(const int& i, const int& j) {
	if (i) return prefix_sum(j) - prefix_sum(i - 1);
	return prefix_sum(j);
}

void Fenwick::update_element(const int& index, const int& value) {
	int diff = value - orignial_array[index];
	if (!diff) return;
	int curr_index = index + 1;
	while (curr_index < fenwick_tree.size()) {
		fenwick_tree[curr_index]+=diff;
		curr_index = calc_next(curr_index);
	}
	orignial_array[index] = value;
}

int main() {
	vector<int> range_array;
	int size;
	cout << "Enter the size of array"<<endl;
	cin >> size;
	range_array.resize(size);
	cout << "Enter elements"<<endl;
	for (int i = 0; i < size; i++) {
		cin >> range_array[i];
	}
	Fenwick new_tree(range_array);
	int start, end;
	cout << "Enter the start index greater than equal to 0"<<endl;
	cin >> start;
	cout << "Enter the end index less than "<<size<<endl;
	cin >> end;
	cout << new_tree.find_range_sum(start, end)<<endl;
	char choice = 'N';
	cout << "Do you want to change and try?(Y/N)" << endl;
	cin >> choice;
	if (tolower(choice) == 'y') {
		int index, val;
		cout << "Enter change index" << endl;
		cin >> index;
		cout << "Enter change val" << endl;
		cin >> val;
		new_tree.update_element(index, val);
		cout << "Enter the start index greater than equal to 0" << endl;
		cin >> start;
		cout << "Enter the end index less than " << size << endl;
		cin >> end;
		cout << new_tree.find_range_sum(start, end);
	}
	return 0;
}