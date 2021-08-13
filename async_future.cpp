#include<iostream>
#include<math.h>
#include<thread>
#include<functional>
#include<future>
#include<chrono>

using namespace std;

int total_primes(int left,int right) {
    int total = 0;
    for (int curr = left; curr <= right; curr++) {
        int i = 2;
        for (; i < curr; i++) {
            if (!(curr % i)) break;
        }
        if (i == curr) ++total;
    }
    return total;
}

int main() {
    future<int> result = async(total_primes, 2, 20);
    shared_future<int> shared_result = result.share();
    bool flag = false;
    cout << "Counting primes in the range..."<<endl;
    if (shared_result.wait_for(chrono::microseconds(1000)) == future_status::timeout) {
        cout << "Still counting..." << endl;
    }
    else {
        flag = true;
        cout << "Number of primes are: " << shared_result.get() << endl;
        cout << "Number of Non-primes are: " <<20-2-shared_result.get() << endl;
    }
    if(!flag){
        cout << "Number of primes are: " << shared_result.get() << endl;
        cout << "Number of Non-primes are: " << 20 - 2 - shared_result.get() << endl;
    }
    return 0;
}