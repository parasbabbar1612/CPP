#include<iostream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

bool check_match(string text, string check) {
       if (text == check) return false;
        int start = 0;
        vector<int> all_pos;
        for (int i = 0; i < check.length(); i++) {
            int pos = text.find(check[i], start);
            if (pos == string::npos) return false;
            all_pos.push_back(pos);
            start = pos + 1;
        }
        int st = 0;
        int en = all_pos.size() - 1;
        if (text.substr(all_pos[st], all_pos[en] - all_pos[st] + 1) == check){
            if (all_pos[en] == text.length() - 1) return false;
            if(text.find(text[all_pos[en]], all_pos[en] + 1) == string::npos) return false;
        }
        return true;
}

inline void lower_case(string& s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

int findKangarooScore(vector<string> words, vector<string> wordsToSynonyms, vector<string> wordsToAntonyms) {
    unordered_map<string, vector<string>> synonyms;
    unordered_map<string, vector<string>> antonyms;
    for (auto i : wordsToSynonyms) {
        int pos = i.find_first_of(':');
        string word = i.substr(0, pos);
        stringstream ss(i.substr(pos+1));
        string token;
        while (getline(ss, token, ',')) synonyms[word].push_back(token);
    }
    for (auto i : wordsToAntonyms) {
        int pos = i.find_first_of(':');
        string word = i.substr(0, pos);
        stringstream ss(i.substr(pos+1));
        string token;
        while (getline(ss, token, ',')) antonyms[word].push_back(token);
    }
    unordered_map<string, int> syn_pairs;
    unordered_map<string, int> ant_pairs;
    int answer = 0;
    for (auto i : words) {
        for (auto j : synonyms[i]) {
            if (check_match(i, j)) {
                ++answer;
                syn_pairs[j]++;
            }
        }
    }
    for (auto i : words) {
        for (auto j : antonyms[i]) {
            if (check_match(i, j)) {
                --answer;
                ant_pairs[j]++;
            }
        }
    }
    for (auto i : syn_pairs) if (i.second == 2) ++answer;
    for (auto i : ant_pairs) if (i.second == 2) ++answer;
    return answer;
}

int main() {
    vector<string> words{ "aStouND","DeSK","AmicABLe","blossOM","hEllo","AniMOsity","BARren","cUrTaiL","DePArTed","ScioN","gOOdBYE" };
    vector<string> synonyms{ "GOOdbye:aDIeu,Adios,ciAO,paRTINg","ANIMOSITY:haTe","BaRren:baRE","sCioN:SoN,HEir,bRaNCH","curtaIL:cUt" };
    vector<string> antonymns{ "animoSiTY:aMIty","HeLLO:gOOdByE" };
    for (auto& i : words) lower_case(i);
    for (auto& i : synonyms) lower_case(i);
    for (auto& i : antonymns) lower_case(i);
    cout << findKangarooScore(words, synonyms, antonymns);
    return 0;
}