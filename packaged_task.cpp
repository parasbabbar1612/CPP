#include<iostream>
#include<math.h>
#include<thread>
#include<functional>
#include<future>

using namespace std;

class my_func {
public:
    int operator()(int a, int b) const{
        return pow(a, b);
    }
};

int f(int a, int b) {
    return pow(a, b);
}

void task_lambda() {
    packaged_task<int(int, int)> task([](int a, int b) {return pow(a, b); });
    future<int> future_var = task.get_future();
    task(2, 9);
    cout << "Value is:" << future_var.get()<<endl;
}

void task_functor() {
    my_func m1;
    packaged_task<int(int, int)> task(m1);
    future<int> future_var = task.get_future();
    task(2, 9);
    cout << "Value is: " << future_var.get() << endl;
}

void task_thread() {
    packaged_task<int()> task(bind(f, 2, 9));
    future<int> future_var = task.get_future();
    thread t(move(task));
    t.join();
    cout << "Value is: " << future_var.get() << endl;
}

int main() {
    task_functor();
    task_lambda();
    task_thread();
    return 0;
}