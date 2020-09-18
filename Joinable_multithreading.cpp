#include <thread>
#include <iostream>
#include<chrono>

using namespace std;

void thread_ops() {
    cout << "A new thread has started"<<endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Processing done!" << endl;
}

int main() {
    cout << "Main function has started executing..." << endl;
    cout << "Spawning a new process..." << endl;
    thread t1(thread_ops);
    cout << "Is the child process alive? ";
    if (t1.joinable()) cout << "true";
    else cout<< "false";
    cout<< endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Is the child process alive? ";
    if (t1.joinable()) cout << "true";
    else cout << "false";
    cout << endl;
    cout << "Main thread waitng for child thread to exit" << endl;
    t1.join();
    cout << "Is the child process alive? ";
    if (t1.joinable()) cout << "true";
    else cout << "false";
    cout << endl;
    return 0;
}