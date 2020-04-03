#include<iostream>
#include<memory>

using namespace std;

template<class T> class Node
{
public:
	shared_ptr<T> value;
	shared_ptr<Node<T>> next;
	Node<T>() {};
	Node<T>(T x) 
	{
		value = make_shared<T>(x); 
	}
};

template<class T> class Linkedlist
{
public:
	shared_ptr<Node<T>> head;
	Linkedlist<T>() {};
	Linkedlist<T>(const initializer_list<T> &l)
	{
		auto it = l.end() - 1;
		shared_ptr<Node<T>> connect_last;
		while (it != l.begin() - 1)
		{
			shared_ptr<Node<T>> p = make_shared<Node<T>>(*it);
			p->next = head;
			head = p;
			if (p->next == nullptr) connect_last = p;
			it--;
		}
		connect_last->next = head;
		cout << "Initializer List" << endl;
	}
	~Linkedlist<T>()
	{
		head->next.reset();
	}
	Linkedlist<T>(const Linkedlist<T> &obj)
	{
		if (!obj.head) return;
		shared_ptr<Node<T>> p1 = make_shared<Node<T>>();
		head = p1;
		shared_ptr<Node<T>> con=p1;
		shared_ptr<Node<T>> make_list = obj.head->next;
		while (make_list!= obj.head)
		{
			shared_ptr<Node<T>> p2 = make_shared<Node<T>>();
			p2->next = head;
			head = p2;
			make_list = make_list->next;
		}
		con->next = head;
		head->value = make_shared<T>(*(obj.head->value));
		p1 = obj.head->next;
		shared_ptr<Node<T>> p2 = head->next;
		while (p1 != obj.head)
		{
			p2->value = make_shared<T>(*(p1->value));
			p2 = p2->next;
			p1 = p1->next;
		}
		cout << "Copy Constructor" << endl;
	}
	void operator=(const Linkedlist<T>& obj)
	{
		if (head)
		{
			head->next.reset();
			head.reset();
		}
		shared_ptr<Node<T>> p1 = make_shared<Node<T>>();
		head = p1;
		shared_ptr<Node<T>> con = p1;
		shared_ptr<Node<T>> make_list = obj.head->next;
		while (make_list != obj.head)
		{
			shared_ptr<Node<T>> p2 = make_shared<Node<T>>();
			p2->next = head;
			head = p2;
			make_list = make_list->next;
		}
		con->next = head;
		head->value = make_shared<T>(*(obj.head->value));
		p1 = obj.head->next;
		shared_ptr<Node<T>> p2 = head->next;
		while (p1 != obj.head)
		{
			p2->value = make_shared<T>(*(p1->value));
			p2 = p2->next;
			p1 = p1->next;
		}
		cout << "L-value Assignment Operator" << endl;
	}
};

template<class T> ostream& operator<<(ostream& str, const Linkedlist<T>& obj)
{
	if (obj.head->value == nullptr) str << "0 ";
	else str << *(obj.head->value)<<" ";
	shared_ptr<Node<T>> p = obj.head->next;
	while (p!=obj.head) 
	{
		str << *(p->value)<<" ";
		p = p->next;
	}
	return str;
}

int main()
{
	Linkedlist<int> l1{1,2,3,4,5};
	Linkedlist<int> l2{ l1 };
	cout << l1 << endl;
	cout << l2<<endl;
	shared_ptr<int> val= make_shared<int>(10);
	l2.head->value = val;
	cout << l2 << endl;
	cout << l1 << endl;
	Linkedlist<int> l3;
	l3 = l1;
	cout << l3 << endl;
	return 0;
}