#include <thread>
#include <iostream>
#include<algorithm>
#include<chrono>

using namespace std;

bool flag = true;

void count_ops(string name) {
    int count = 0;
    while (flag) {
        ++count;
    }
    cout <<"Operations Perfromed by " <<name<<count<<endl;;
}

int main() {
    thread t1(count_ops, "Thread_1");
    thread t2(count_ops, "Thread_2");
    this_thread::sleep_for(chrono::seconds(1));
    flag = false;
    t1.join();
    t2.join();
    return 0;

}