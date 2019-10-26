#include <iostream>

using namespace std;

int main()
{
int n;
int length,breadth;
cout<<"\n Enter the length of the rectangle";
cin>>length;
cout<<"\n Enter the breadth of the rectangle";
cin>>breadth;
int i,j;
for (i=1;i<=length;i++)
{
    for (j=1;j<=breadth;j++)
    {
        cout<<"*";
    }

    cout<<"\n";
}
}