#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
#include<string>

using namespace std;

string compressed(string& s, int k) {
    if (s.length() < k) return s;
    unordered_set<int> check;
    for (auto i : s) check.insert(i);
    while (s.length() > k) {
        int count = 0;
        for (auto i : check) {
            string temp(k,i);
            int pos = s.find(temp);
            if (pos != string::npos) {
                s = s.substr(0, pos) + s.substr(pos + k);
                ++count;
            }
        }
        if (count == 0) break;
    }
    return s;
}

 int main() {
     string s = "baac";
     cout <<compressed(s, 2);
     return 0;
}