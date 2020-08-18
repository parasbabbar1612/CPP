#include<iostream>
#include<unordered_set>
#include<vector>

using namespace std;

vector<string> find_all_unq(string s, int k) {
    if (s.length() < k || k>s.length) return {};
    unordered_set<string> unique_comb;
    int left = 0, right = 0;
    vector<int> freq(26);
    while (right < s.length()) {
        if ((right - left+1) <=k) {
            freq[s[right] - 'a']++;
        }
        if (freq[s[right] - 'a'] > 1) {
            while (freq[s[right] - 'a'] > 1) {
                freq[s[left]-'a']--;
                ++left;
            }
        }
        else if ((right - left+1) == k) {
            unique_comb.insert(s.substr(left, right - left+1));
            freq[s[left]-'a']--;
            ++left;
        }
        ++right;
    }
    vector<string> answer;
    for (auto i : unique_comb) answer.push_back(i);
    return answer;
}

int main() {
    string s = "awaglknagawunagwkwagl";
    vector<string> answer = find_all_unq(s, 4);
    for (auto i : answer) {
        for (auto j : i) cout << j;
        cout << endl;
    }
    return 0;
}