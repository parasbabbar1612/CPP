#include<iostream>
#include<thread>
#include<atomic>
#include<assert.h>

using namespace std;

atomic<int> var1, var2, var3, var4;
atomic<bool> sync1, sync2;

void thread1() {
    var1.store(10, memory_order_relaxed);
    var2.store(20, memory_order_relaxed);
    var3.store(30, memory_order_relaxed);
    var4.store(40, memory_order_relaxed);
    sync1.store(true, memory_order_release);
}

void thread2() {
    while (!sync1.load(memory_order_acquire));
    sync2.store(true, memory_order_release);
}

void thread3() {
    while (!sync2.load(memory_order_acquire));
    assert(var1 == 10);
    assert(var2 == 20);
    assert(var3 == 30);
    assert(var4 == 40);
    cout << var1 << " " << var2 << " " << var3 << " " << var4 << endl;
}

int main() {
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}