#include <iostream>
#include <string>

using namespace std;

int main()
{
    
    char name[40];
    string add;
    cout<<"\n Enter your name";
    cin.getline(name,40);
    cout<<"\n Enter your address";
    getline(cin,add);
    cout<<name;
    cout<<add;
}
