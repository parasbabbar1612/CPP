#include<iostream>
#include<unordered_map>

using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode*> map;
    bool isend;
    TrieNode() :isend(false) {};
};
TrieNode* root;
class Trie
{
public:
    Trie(){ root = new TrieNode;}
    void insert(string s)
    {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++)
        {
            TrieNode* new_node = new TrieNode;
            if (curr->map.find(s[i]) == curr->map.end())
            {
                curr->map[s[i]] = new_node;
                curr = new_node;
            }
            else curr = curr->map[s[i]];
        }
        curr->isend = true;
    }
    bool whole_find(string s)
    {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++)
        {
            if (curr->map.find(s[i]) == curr->map.end()) return false;
            curr = curr->map[s[i]];
        }
        if (!curr->isend) return false;
        return true;
    }
    bool validate_present_prefix(string prefix)
    {
        TrieNode* curr = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            if (curr->map.find(prefix[i]) == curr->map.end()) return false;
            curr = curr->map[prefix[i]];
        }
        if (curr->map.size() == 0) return false;
        return true;
    }
};
int main()
{
    Trie *new_trie = new Trie();
    new_trie->insert("abc");
    new_trie->insert("abgl");
    new_trie->insert("lmn");
    new_trie->insert("pqrs");
    cout<<new_trie->whole_find("pqr")<<endl;
    cout << new_trie->validate_present_prefix("l") << endl;
    return 0;
}