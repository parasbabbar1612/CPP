#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;

class Comp {
public:
    int sort_order;
    int sort_param;
    Comp() {};
    Comp(int sort_or,int sort_p) :sort_order(sort_or), sort_param(sort_p) {};
    bool operator()(const pair<string, pair<int, int>>& p1, const pair<string, pair<int, int>>& p2) const {
        switch (sort_param) {
        case 0: return sort_order == 0 ? p1.first<p2.first : p1.first>p2.first;
        case 1: return sort_order == 0 ? p1.second.first<p2.second.first : p1.second.first>p2.second.first;
        case 2: return sort_order == 0 ? p1.second.second<p2.second.second : p1.second.second>p2.second.second;
        }
        return true;
    }
};

vector<string> find_pages(unordered_map<string, pair<int, int>>& items, int order,int parameter,int page_num,int items_page) {
    Comp c1(order,parameter);
    vector<string> answer;
    vector<pair<string, pair<int, int>>> temp;
    for (auto i : items) {
        temp.push_back(i);
    }
    sort(temp.begin(), temp.end(), c1);
    int start = page_num * items_page;
    int end = start + items_page;
    for (int i = start; i < end; i++) {
        if (i >= temp.size()) break;
        answer.push_back(temp[i].first);
    }
    return answer;
}

int main() {
    unordered_map<string, pair<int, int>> items{ {"Item1", { 10,15 }},{"Item2", { 3,4 }},{"Item3", { 17,8 }} };
    for (auto i : find_pages(items, 0, 1, 1, 2)) cout << i << " ";
    return 0;
}