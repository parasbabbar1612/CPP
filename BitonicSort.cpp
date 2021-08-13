//HW1 By Paras Babbar

//SU Net Id:pbabbar SUID:418085055

#include<iostream>
#include<vector>
#include<chrono>
#include<thread>

using namespace std;

//Recursive function to sort the vector using bitonic sort and it is used by single threaded function as well as multi-threaded function

void sort_parts(vector<int>& curr_array, const int& start, const int& size, const int& end, const int& check_sign) {
	if (size == 1) return;
	int comp_distance = size / 2;
	int increment = comp_distance == 1 ? 2 : 1;
	for (int i = start; i < end - comp_distance; i += increment) {
		if (!(check_sign % 2)) {
			if (curr_array[i] > curr_array[i + comp_distance]) {
				int temp = curr_array[i];
				curr_array[i] = curr_array[i + comp_distance];
				curr_array[i + comp_distance] = temp;
			}
		}
		else {
			if (curr_array[i] < curr_array[i + comp_distance]) {
				int temp = curr_array[i];
				curr_array[i] = curr_array[i + comp_distance];
				curr_array[i + comp_distance] = temp;
			}
		}
	}
	int mid = (start + end) / 2;
	sort_parts(curr_array, start, size / 2, mid, check_sign);
	sort_parts(curr_array, mid, size / 2, end, check_sign);
}

// A helper sorter function to perform comparisons when the comparison distance is large enough and can't be processed using our traditional 4 threads

void sorter(vector<int>& curr_array, int start, int end, int check_sign) {
	int comp_distance = (end - start) / 2;
	for (int i = start; i < end - comp_distance; i++) {
		if (!(check_sign % 2)) {
			if (curr_array[i] > curr_array[i + comp_distance]) {
				int temp = curr_array[i];
				curr_array[i] = curr_array[i + comp_distance];
				curr_array[i + comp_distance] = temp;
			}
		}
		else {
			if (curr_array[i] < curr_array[i + comp_distance]) {
				int temp = curr_array[i];
				curr_array[i] = curr_array[i + comp_distance];
				curr_array[i + comp_distance] = temp;
			}
		}
	}
}


//Used by multiple threads based to split the vector to do parallel processing

void multi_sort_split(vector<int>& curr_array, int start, int end, int parent, int sub_array_size) {
	while (sub_array_size <= (end - start)) {
		for (int i = start; i < end; i += sub_array_size) {
			int curr_parent = parent == -1 ? i / sub_array_size : parent;
			sort_parts(curr_array, i, sub_array_size, i + sub_array_size, curr_parent);
		}
		sub_array_size *= 2;
	}
}

//Main entry point of our multi-threaded bitonic sort algorithm

void multi_threaded_bitonic_sort(vector<int>& curr_array) {
	int n = curr_array.size();
	thread t1, t2, t3;

	//Checking n>=4 so that when the size of the vector is less than 4 and our vector can't be split into 4 parts for multiple threads there is no need to parallel processing and also to avoid crashing of the program

	if (n >= 4) {
		t1 = thread(multi_sort_split, ref(curr_array), 0, n / 4, -1, 2);
		t2 = thread(multi_sort_split, ref(curr_array), n / 4, n / 2, -1, 2);
		t3 = thread(multi_sort_split, ref(curr_array), n / 2, (3 * n) / 4, -1, 2);
		multi_sort_split(curr_array, (3 * n) / 4, n, -1, 2);
		t1.join();
		t2.join();
		t3.join();
		t1 = thread(sorter, ref(curr_array), 0, n / 2, 0);
		sorter(curr_array, n / 2, n, 1);
		t1.join();
		t1 = thread(multi_sort_split, ref(curr_array), 0, n / 4, 0, n / 4);
		t2 = thread(multi_sort_split, ref(curr_array), n / 4, n / 2, 0, n / 4);
		t3 = thread(multi_sort_split, ref(curr_array), n / 2, (3 * n) / 4, 1, n / 4);
		multi_sort_split(curr_array, (3 * n) / 4, n, 1, n / 4);
		t1.join();
		t2.join();
		t3.join();
	}
	sorter(curr_array, 0, n, 0);
	if (n >= 4) {
		t1 = thread(sorter, ref(curr_array), 0, n / 2, 0);
		sorter(curr_array, n / 2, n, 0);
		t1.join();
		t1 = thread(multi_sort_split, ref(curr_array), 0, n / 4, 0, n / 4);
		t2 = thread(multi_sort_split, ref(curr_array), n / 4, n / 2, 0, n / 4);
		t3 = thread(multi_sort_split, ref(curr_array), n / 2, (3 * n) / 4, 0, n / 4);
		multi_sort_split(curr_array, (3 * n) / 4, n, 0, n / 4);
		t1.join();
		t2.join();
		t3.join();
	}
}

//Main entry point of our single thread bitonic sort algorithm

void single_threaded_bitonic_sort(vector<int>& curr_array) {
	int sub_array_size = 2;
	while (sub_array_size <= curr_array.size()) {
		for (int i = 0; i < curr_array.size(); i += sub_array_size) {
			sort_parts(curr_array, i, sub_array_size, i + sub_array_size, i / sub_array_size);
		}
		sub_array_size *= 2;
	}
}

//Funtion that returns true if the size of the input is a power of 2 else returns false

int main() {
	int size;
	cout << "Enter the size of the array(value >=0) original size will be 2 ^ size" << endl;
	cin >> size;
	while (size < 0) {
		cout << "Please enter valid size(0 or greater)" << endl;
		cin >> size;
	}
	//Filling our input array with random value from 0-1000

	size = pow(2, size);
	vector<int> input_array;
	for (int i = 0; i < size; i++) {
		input_array.emplace_back(rand() % 1000);
	}

	cout << "Original array" << endl;
	cout << endl;
	for (auto i : input_array) {
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	//Intializing vectors for single and multi threaded processing

	vector<int> single_thread_processing(input_array.begin(), input_array.end());
	vector<int> multi_thread_processing(input_array.begin(), input_array.end());

	//Capturing start time for single thread processing
	chrono::system_clock::time_point start_s = chrono::system_clock::now();

	//Single thread bitonic sort algorithm processing
	single_threaded_bitonic_sort(single_thread_processing);

	//Capturing end time for single thread processing
	chrono::system_clock::time_point end_s = chrono::system_clock::now();

	//Total time for single thread bitonic sort algorithm
	chrono::system_clock::duration total_time = end_s - start_s;


	cout << "Sorted array using single thread" << endl;
	cout << endl;
	for (auto i : single_thread_processing) {
		cout << i << " ";
	}
	cout << endl;
	cout << endl;


	//Capturing start time for multi threaded processing
	chrono::system_clock::time_point start_m = chrono::system_clock::now();

	//Multi-threaded bitonic sort algorithm processing
	multi_threaded_bitonic_sort(multi_thread_processing);

	//Capturing end time for multi threaded processing
	chrono::system_clock::time_point end_m = chrono::system_clock::now();

	//Total time for single thread bitonic sort algorithm
	chrono::system_clock::duration total_time_m = end_m - start_m;

	cout << "Sorted array using multiple threads" << endl;
	cout << endl;
	for (auto i : multi_thread_processing) {
		cout << i << " ";
	}
	cout << endl;
	cout << endl;

	cout << "Execution time for bitonic sort with single thread: " << chrono::duration_cast<chrono::microseconds>(total_time).count() << "ms" << endl;
	cout << "Execution time for bitonic sort with four threads: " << chrono::duration_cast<chrono::microseconds>(total_time_m).count() << "ms" << endl;
	return 0;
}