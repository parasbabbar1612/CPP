#include<iostream>
#include<shared_mutex>
#include<thread>
#include<chrono>

using namespace std;

shared_mutex thr_lock;

unsigned int process_items = 0;

void process_read() {
    thr_lock.lock_shared();
    cout << "Thread reading the value is " << this_thread::get_id()<<" Value is"<<process_items<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    thr_lock.unlock_shared();
}
void process_write() {
    thr_lock.lock();
    cout << "Thread writing the value is " << this_thread::get_id() << endl;
    process_items++;
    this_thread::sleep_for(chrono::seconds(1));
    thr_lock.unlock();
}
int main() {
    cout << "Main thread is being executed"<<endl;
    thread newt1(process_read);
    thread newt2(process_write);
    thread newt3(process_read);
    thread newt4(process_write);
    thread newt5(process_read);
    thread newt6(process_read);
    thread newt7(process_read);
    newt1.join();
    newt2.join();
    newt3.join();
    newt4.join();
    newt5.join();
    newt6.join();
    newt7.join();
    cout << "Processing completed" << endl;
    return 0;
}