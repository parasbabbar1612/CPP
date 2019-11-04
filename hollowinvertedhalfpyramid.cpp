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
        	if (i==0)
        	{
        	    cout<<"*";
        	}
        	else if (i>0 && (j == 0 || j == length-i-1))
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

*****
 ***
  *