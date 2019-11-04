#include<iostream>

using namespace std;

int main()
{
    int dd,mm,yy,total;
    int A[]={31,28,31,30,31,30,31,31,30,31,30,31};
    cout<<"\n Enter dd";
    cin>>dd;
    cout<<"\n Enter mm";
    cin>>mm;
    cout<<"\n Enter yy";
    cin>>yy;
    total=dd;
    for(int i=0;i<mm-1;i++) total+=A[i];
    if (yy%4==0) total+=1;
    cout<<"Total no of days are"<<" "<<total;
}