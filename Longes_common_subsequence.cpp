#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class comp
{
public:
    bool operator()(const vector<char>& v1, const vector<char>& v2)
    {
        return v1.size() < v2.size();
    }
};

int longest_common_subsequence(vector<vector<char>>& subsequence, const string& s1, const string& s2)
{
    if (!s1.length() || !s2.length()) return 0;
    vector<char> temp;
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1));
    for (int i = 0; i < s1.length(); i++)
        for (int j = 0; j < s2.length(); j++)
        {
            if (s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                temp.push_back(s1[i]);
                subsequence.push_back(temp);
                if (subsequence.size() > 1) subsequence.push_back({ s1[i] });
            }
            else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        }
    return dp[s1.length()][s2.length()];
}

int main()
{
    comp c1;
    string s1 = "abcde";
    string s2 = "ace";
    vector<vector<char>> subsequence;
    int max_len = longest_common_subsequence(subsequence, s1, s2);
    cout << "Length of longest common subsequence of these 2 strings is :" << max_len << endl;
    sort(subsequence.begin(), subsequence.end(),c1);
    cout << "All common subsequences are :" << endl;
    for (auto i : subsequence)
    {
        for (auto j : i) cout << j << ",";
        cout << endl;
    }
    return 0;
}