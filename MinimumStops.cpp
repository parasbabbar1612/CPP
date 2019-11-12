#include <iostream>

using namespace std;

int main()
{
int n,d,i,j,distance;
cout<<"\n Enter number of possible stopping point";
cin>>n;
int A[n];
cout<<"\n Enter the maximum distance that can be travelled in a day";
cin>>d;
cout<<"\n Enter total journey distance";
cin>>distance;
cout<<"\n Enter the stopping points";
for(int j=0;j<n;j++)
{
cin>>A[j]; 
}
A[n+1]=distance;
for (j=1;j<n;j++)
{
A[j]=A[j]-A[j-1];
}
int sum=0,count=0;
for (i=0;i<n;i++)
    {
        
        if (A[i]==d) count+=1;
        else
        {
        count+=1;    
        sum=0;
        while (sum<=d)
        {
        sum+=A[i];
        ++i;
        }
        --i;
        }
    }    
cout<<"\n Mimimum Number of stops = "<<count;
    }
