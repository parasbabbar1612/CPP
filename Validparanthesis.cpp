#include <stack>
class Solution {
public:
    bool isValid(string s) {
        stack <char> p;
        for(int i=0;i<s.length();i++)
        {
        if((s[i]==')'||s[i]=='}'||s[i]==']') && (p.empty()==true)) return false;
        if(s[i]=='('||s[i]=='{'||s[i]=='[') p.push(s[i]);
        if(s[i]==')' && p.top()=='(') 
        { 
         p.pop();
         continue;
        }
        if(s[i]==')'&& (p.top()=='['||p.top()=='{')) return false;
        if(s[i]==']' && p.top()=='[') 
        { 
         p.pop();
         continue;
        }
        if(s[i]==']' && (p.top()=='('||p.top()=='{')) return false;   
        if(s[i]=='}' && p.top()=='{') 
        { 
         p.pop();
         continue;
        }
        if(s[i]=='}' && (p.top()=='('||p.top()=='[')) return false;
        }
        if (p.empty()) return true;
            else return false;
    }};
        
        