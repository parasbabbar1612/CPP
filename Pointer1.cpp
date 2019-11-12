
#include <iostream>

using namespace std;

int main()
{
    int* p1=new int(100); //Initialising p1 to hold the Address of integer 100
    cout<<"Address"<<p1<<" "<<"Element"<<*p1; //Displaying Address stored in p1 and value stored in that Address
    int j=99;
    p1=&j; //Assigning p1 to point to integer j
    cout<<"New Address"<<p1<<" "<<"New element"<<*p1;//Displaying Address stored in p1 and value stored in that Address

    
}
