#include<vector>
#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void merge_sort(int start,int end,vector<int>& og) {
	int mid = (start + end) / 2;
	int i = start;
	int j = mid + 1;
	vector<int> temp_array(end - start + 1);
	int k = 0;
	while (i <= mid && j <= end) {
		if (og[i] > og[j]) {
			temp_array[k++] = og[j];
			++j;
		}
		else if (og[i] < og[j]) {
			temp_array[k++] = og[i];
			++i;
		}
		else {
			temp_array[k++] = og[j];
			temp_array[k++] = og[i];
			++i;
			++j;
		}
	}
	for (; i <= mid; i++) {
		temp_array[k++] = og[i];
	}
	for (; j <= end; j++) {
		temp_array[k++] = og[j];
	}
	k = 0;
	for (int idx = start; idx <= end; idx++) {
		og[idx] = temp_array[k++];
	}
}

void merge(int start, int end, vector<int>& og) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge(start, mid, og);
		merge(mid+1,end,og);
		merge_sort(start, end,og);
	}
}

int main() {
	vector<int> og,og_s;
	int size = 20000;
	for (int i = 0; i < size; i++) {
		int num = rand() % 100;
		og.emplace_back(num);
		og_s.emplace_back(num);
	}
	chrono::system_clock::time_point start = chrono::system_clock::now();
	thread t1(merge,0,(size/4)-1,ref(og));
	thread t2(merge, size/4, (size /2) - 1, ref(og));
	thread t3(merge, size/2, ((3*size)/ 4) - 1, ref(og));
	thread t4(merge, (3 * size) / 4, size - 1, ref(og));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t1 = thread(merge_sort, 0, (size / 2) - 1,ref(og));
	t2 = thread(merge_sort, size/2,size-1,ref(og));
	t1.join();
	t2.join();
	merge_sort(0, size - 1, og);
	chrono::system_clock::time_point end = chrono::system_clock::now();
	chrono::system_clock::duration total_t = end - start;
	
	chrono::system_clock::time_point start_s = chrono::system_clock::now();
	merge(0, size - 1, og_s);
	chrono::system_clock::time_point end_s = chrono::system_clock::now();
	chrono::system_clock::duration total_t_s = end_s - start_s;
	/*
	for (auto i : og) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : og_s) {
		cout << i << " ";
	}
	*/
	cout << "Time taken by four threads: "<< chrono::duration_cast<chrono::microseconds>(total_t).count()<<"ms"<<endl;
	cout << "Time taken by single thread: " << chrono::duration_cast<chrono::microseconds>(total_t_s).count()<<"ms"<<endl;

	return 0;
}