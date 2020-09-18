#include <thread>
#include <iostream>
#include<chrono>

using namespace std;

void detach_thread() {
    cout << "A new thread has started"<<endl;
    while (true) {
        cout << "Child thread is still executing" << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
    
    cout << "Processing done!" << endl;
}

int main() {
    cout << "Main function has started executing..." << endl;
    cout << "Spawning a new process..." << endl;
    thread t1(detach_thread);
    t1.detach();
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Main thread exiting.." << endl;
    return 0;
}