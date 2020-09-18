#include <thread>
#include <iostream>
#include<chrono>

using namespace std;

int count_ops = 0;

void data_race() {
    cout << "A new thread has started"<<endl;
    for (int i = 0; i < 100000; i++) ++count_ops;
    cout << "Processing done!" << endl;
}

int main() {
    cout << "Main function has started executing..." << endl;
    cout << "Spawning a new process..." << endl;
    thread t1(data_race);
    thread t2(data_race);
    t1.join();
    t2.join();
    cout <<count_ops<< endl;
    return 0;
}