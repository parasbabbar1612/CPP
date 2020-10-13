#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool kmp_pattern_match(const string &pattern,const string &text,const vector<int> &pre_suf){
    int p1 = 0, p2 = 0;
    while (p2 < text.length()) {
        if (pattern[p1] == text[p2]) {
            ++p1;
            ++p2;
            if (p1 == pattern.length()) return true;
        }
        else {
            if (p1 > 0) p1 = pre_suf[p1 - 1];
            else ++p2;
        }
    }
    return false;
}

int main() {
    string text, pattern;
    cout << "Enter the text" << endl;
    getline(cin,text,'\n');
    cout << "Enter the pattern to be searched" << endl;
    getline(cin, pattern,'\n');
    vector<int> pre_suf(pattern.length());
    int i = 0, j = 1;
    while (j < pattern.length()) {
        if (pattern[i] == pattern[j]) {
            pre_suf[j] = i + 1;
            ++i;
            ++j;
        }
        else if (pattern[i] != pattern[j]) {
            if (i > 0 && pre_suf[i-1]) i = pre_suf[i - 1];
            else ++j;
        }
    }
    cout << boolalpha<<kmp_pattern_match(pattern, text, pre_suf);
    return 0;
}