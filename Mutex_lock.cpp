#include <thread>
#include <iostream>
#include<chrono>
#include<mutex>

using namespace std;

mutex protector;
int count_ops = 0;

void critical_section() {
    cout << "A new thread has started"<<endl;
    for (int i = 0; i < 10; i++) {
        cout << "Process :" << this_thread::get_id() << " is blocked for IO" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        protector.lock();
        ++count_ops;
        protector.unlock();
    }
    cout << "Processing done!" << endl;
}

int main() {
    cout << "Main function has started executing..." << endl;
    cout << "Spawning a new process..." << endl;
    thread t1(critical_section);
    thread t2(critical_section);
    t1.join();
    t2.join();
    cout <<count_ops<< endl;
    return 0;
}