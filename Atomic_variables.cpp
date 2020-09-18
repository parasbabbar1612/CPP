#include <thread>
#include <iostream>
#include<atomic>

using namespace std;

atomic<int> count_ops = 0;

void critical_section() {
    cout << "A new thread has started"<<endl;
    for (int i = 0; i < 10; i++) {
        ++count_ops;
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