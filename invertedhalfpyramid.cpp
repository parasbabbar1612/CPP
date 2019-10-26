#include <iostream>

using namespace std;

int main()
{
int length;
cout<<"\n Enter the size of pyramid";
cin>>length;
int i,j;
for (i=0;i<length;i++)
{
    for (j=0;j<length-i;j++)
    {
        	cout<<"*";
        	
		}
	cout<<"\n";
}
}