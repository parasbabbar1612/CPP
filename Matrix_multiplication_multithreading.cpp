#include<iostream>
#include<thread>
#include<vector>

using namespace std;

void multiply(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c,int s_r,int e_r,int s_c,int e_c){
	for (int i = s_r; i < e_r; i++) {
		for (int j = s_c; j <e_c; j++) {
			int val = 0;
			for (int k = 0; k < b.size(); k++) {
				val += a[i][k] * b[k][j];
			}
			c[i][j] = val;
		}
	}
}

int main() {
	int row, col, row_, col_;
	cout << "Enter the numbers of rows for Matrix A" << endl;
	cin >> row;
	cout << "Enter the numbers of columns for Matrix A" << endl;
	cin >> col;
	cout << "Enter the numbers of rows for Matrix B" << endl;
	cin >> row_;
	cout << "Enter the numbers of columns for Matrix B" << endl;
	cin >> col_;
	if (col != row_) {
		cout << "Invalid matrix dimensions" << endl;
		return 0;
	}
	vector<vector<int>> a(row, vector<int>(col)), b(row_, vector<int>(col_)), c(row, vector<int>(col_));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			a[i][j] = rand() % 5;
		}
	}
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			b[i][j] = rand() % 5;
		}
	}
	for (auto i : a) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (auto i : b) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	thread t1{multiply,ref(a),ref(b),ref(c),0,row/2,col_/2,col_};
	thread t2{multiply,ref(a),ref(b),ref(c),row/2,row,0,col_/2};
	thread t3{multiply,ref(a),ref(b),ref(c),row/2,row,col_/2,col_};
	multiply(a, b, c, 0, row/2, 0, col_/2);
	t1.join();
	t2.join();
	t3.join();
	cout << endl;
	for (auto i : c) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}
