#include<iostream>

using namespace std;

class node
{
public:
	int data;
	node *next;
};
node* head = NULL;
node* tail = NULL;

void addnode(int val)
{
	node *temp = new node;
	temp->data = val;
	temp->next = NULL;
	if (head == NULL || tail == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
   else
	{
		tail->next = temp;
		tail = temp;
	}
	
}

int main()
{
	int n,val;
	cout << "\n Enter the number of nodes u want to enter";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\n Enter node";
		cin >> val;
		addnode(val);
		}
	    node* p = head;
		while (p != NULL)
		{
			cout << p->data << endl;
			p = p->next;
		}	
}