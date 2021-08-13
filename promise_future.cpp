#include<iostream>
#include<thread>
#include<functional>
#include<future>

using namespace std;

void set_value(future<int>& fut) {
    int val = fut.get();
    cout << val << endl;
}

int main() {
    promise<int> new_promise;
    future<int> result=new_promise.get_future();
    thread t1(set_value, ref(result));
    new_promise.set_value(50);
    t1.join();
    return 0;
}