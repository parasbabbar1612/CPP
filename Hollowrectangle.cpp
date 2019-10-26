#include <iostream>

using namespace std;

int main()
{
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
        if (i==1 || i==length|| j==1 || j==breadth)
		{
			cout<<"*";
		}
		else
		{
			cout<<" ";
		}
    }

    cout<<"\n";
}
}