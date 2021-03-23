#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

recursive_mutex thr_lock;
unsigned int count1 = 0;
unsigned int count2 = 0;
void inc_1() {
    thr_lock.lock();
    ++count1;
    thr_lock.unlock();
}
void inc_2() {
    thr_lock.lock();
    ++count2;
    inc_1();
    thr_lock.unlock();
}
void helper() {
    for (int i = 0; i < 10000; i++) {
        inc_1();
        inc_2();
    }
}
int main() {
    cout << "Main thread is being executed"<<endl;
    thread newt1(helper);
    thread newt2(helper);
    newt1.join();
    newt2.join();
    cout << "Counter 1= " << count1 << endl;
    cout << "Counter 2= " << count2 << endl;
    return 0;
}