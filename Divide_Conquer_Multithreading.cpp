#include<iostream>
#include<future>

using namespace std;

long long add_func(int low, int high, int depth) {
    long long sum = 0;
    if (depth > 3) {
        for (int i = low; i <high; i++) {
            sum += i;
        }
        return sum;
    }
    else {
        int mid = (low + high) / 2;
        auto l_sum = async(launch::async, add_func, low, mid, depth + 1);
        auto r_sum = add_func(mid, high, depth + 1);
        return l_sum.get() + r_sum;
    }
}

int main() {
    cout << "Main thread started" << endl;
    cout << "Total sum value is = " << add_func(0, 1000000000,0)<< endl;
    return 0;
}