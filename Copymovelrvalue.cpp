#include<iostream>

using namespace std;

class Node
{
public:
	int data;
	Node* next;
	Node()
	{
		next = nullptr;
	}
	Node(int x)
	{
		data = x;
		next = nullptr;
	}
	
};
class Linkedlist
{
public:
	Node* head;
	Linkedlist()
	{
		head = nullptr;
	}
	Linkedlist(const initializer_list<int>& l)
	{
		head = nullptr;
		for(auto i:l)
		{
			Node* p = new Node(i);
			p->next = head;
			head = p;
		}
		cout << "Initializer list" << endl;
	}
	Linkedlist(const Linkedlist& l) :Linkedlist()
	{
		Node* p = l.head;
		while (p)
		{
			Node* n = new Node();
			n->next = head;
			head = n;
			p = p->next;
		}
		Node* n = head;
		Node* n1 = l.head;
		while (n1)
		{
			n->data = n1->data;
			n = n->next;
			n1 = n1->next;
		}
		cout << "Copy constructor"<<endl;
	}
	Linkedlist(Linkedlist&& l) :Linkedlist()
	{
		head = l.head;
		l.head = nullptr;
		cout << "Move constructor" << endl;
	}
	void operator=(Linkedlist&& l)
	{
		while (head)
		{
			Node* n = head->next;
			delete head;
			head = n;
		}
		head = l.head;
		l.head = nullptr;
		cout << "Rvalue operator=" << endl;
	}

	void operator=(const Linkedlist &l)
	{
		while (head)
		{
			Node* n = head->next;
			delete head;
			head = n;
		}
		Node* p = l.head;
		while (p)
		{
			Node* n = new Node();
			n->next = head;
			head = n;
			p = p->next;
		}
		Node *n = head;
		Node *n1 = l.head;
		while (n1)
		{
			n->data = n1->data;
			n = n->next;
			n1 = n1->next;
		}
		cout << "Operator=" << endl;
	}
	void printlist()
	{
		Node* p = head;
		while (p)
		{
			cout << p->data << " ";
			p = p->next;
		}
	}
	Linkedlist threetimes();
	~Linkedlist()
	{
		while (head)
		{
			Node* n = head->next;
			delete head;
			head = n;
		}
		cout << "Destructor" << endl;

	}
};
Linkedlist Linkedlist::threetimes()
{
  Linkedlist temp(*this);
  Node* p = temp.head;
  while (p)
  {
	  p->data = 3 * p->data;
	  p = p->next;
  }
  return move(temp);
}
int main()
{
	Linkedlist l1{ 1,2,3,4,5 };
	l1.printlist();
	cout << endl;
	Linkedlist l2;
	l2=l1;
	l1.head->data = 10;
	l2.printlist();
	cout << endl;
	Linkedlist l3;
	l3=l1.threetimes();
	cout << endl;
	l3.printlist();
	cout << endl;
	l1.printlist();
	cout << endl;

}