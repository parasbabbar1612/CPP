#include<iostream>
#include<thread>
#include<atomic>
#include<assert.h>
#include<vector>

using namespace std;

atomic_flag lock_stream=ATOMIC_FLAG_INIT;

void sync_threads(int num) {
    while (lock_stream.test_and_set());
    cout << "Thread #" << num << endl;
    lock_stream.clear();
}

int main() {
    vector<thread> all_threads(10);
    for (int i = 0; i < 10; i++) {
        all_threads[i] = thread(sync_threads, i + 1);
    }
    for(auto &i:all_threads) i.join();
    return 0;
}