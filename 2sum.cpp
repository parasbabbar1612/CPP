#include<iostream>

using namespace std;

int main()
{
int n,i,j;
cout<<"\n Enter the length of array";
cin>>n;
int a[n];
int target;
cout<<"\n Enter the target value";
cin>>target;
cout<<"\n Enter elements of array";
for(i=0;i<n;i++)
{
    cin>>a[i];
}
int sum=0;
for(i=0;i<n;i++)
{
    for(j=i+1;j<n;j++)
    {
        sum=a[i]+a[j];
        if (sum==target)
        {
            cout<<i<<","<<j<<endl;
        }

    }
}
}

