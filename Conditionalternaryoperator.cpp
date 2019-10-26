#include <iostream>

using namespace std;

int main()
{
int n;
char c;
cout<<"\n Enter a number";
cin>>n;
n=n % 2==0 ? 1:0;
if (n==1)
{
    cout<<"YES";
}
else
{
    cout<<"NO";
}
}
