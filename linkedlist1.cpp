#include<iostream>

using namespace std;

class node
{
public:
	int data;
	node* next;
};
node* head = NULL;
node* tail = NULL;

void addnode(int val)
{
	node* temp = new node;
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
void delnode(int v)
{
	node* s = head;
	int count = 0;
	while (s != NULL)
	{
		if (s->data == v)
		{
			count++;
			s->data = s->next->data;
			s->next = s->next->next;
		}

		else s = s->next;
	}
	if (count > 0) cout << "\n Found and deleted";
	else cout << "\n Not found";
	cout << "\n The list after insertion and deletion is:" << endl;


}
int main()
{
	int n, val, del;
	cout << "\n Enter the number of nodes u want to enter";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\n Enter node";
		cin >> val;
		addnode(val);
	}
	node* p = head;
	cout << "\n Enter value to be deleted";
	cin >> del;
	delnode(del);
	while (p != NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}
}