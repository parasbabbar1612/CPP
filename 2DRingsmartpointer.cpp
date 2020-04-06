#include <iostream>
#include <memory>

using namespace std;
template <typename T> class Node { //Your T has to support either int or float
public:
	shared_ptr<T> pValue; //pValue is a pointer to an object of type T
	shared_ptr<Node<T>> row_next;//Points to the next node in the same row
	shared_ptr<Node<T>> col_next;//Points to the nexe node in the same col
	Node() {}
	Node(T v) { pValue = make_shared<T>(v); }// pValue.reset(new T(v)); will also work,but slower
};

template <typename T> class Ring2D {
public:
	shared_ptr<Node<T>> head;//Points to the node at first row and first column
	Ring2D() {};

	//Implement the following functions:
	Ring2D(const initializer_list<T>& I); //initializer_list 
	/*
	the first two number in the initializer_list will be number of rows and number of columns
	followed by values in each row
	For example, for  3 4  1 2 3 4  5 6 7 8  9 10 11 12: 3 rows and 4 columns; first row: to 1 2 3 4;
	second row: 5 6 7 8; third row 9 10 11 12
	*/
	~Ring2D();//destructor; whenever possible, you should do minimum work.



	Ring2D(const Ring2D<T>& R);//copy constructor
	void operator=(const Ring2D<T>& R);//Lvalue operator=; copy assignment
	Ring2D(Ring2D<T>&& R);//move constructor
	void operator=(Ring2D<T>&& R);//Rvalue operator=; move assignment
	Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D

	void DeleteRow(int r);//Delete row r of Ring2D
	//If r is out of range, simply do nothing and return.

};

/*
Implement the needed overloaded operater<< such that you can do cout <<Ring2D<T> instance.
For the example described in the above initializer_list, you output should look like:
1 2 3 4
5 6 7 8
9 10 11 12
*/


/*
Print: "Copy Constructor", "Move Constructor", "Copy Assignment", "Move Assignment", "Destructor" when leaving
the corresponding functions --  the same way I did for Lecture on Ring (3/31/2020).


*/

template <class T> Ring2D<T>::Ring2D(const initializer_list<T>& I)
{
	T num_rows = *(I.begin());
	T num_columns = *(I.begin() + 1);
	auto j_start = I.begin() + 1;
	auto j_end = I.begin() + 1 + num_columns;
	shared_ptr<Node<T>> row_start;
	shared_ptr<Node<T>> connect_row;
	shared_ptr<Node<T>> connect_col;
	shared_ptr<Node<T>> track_head;
	for (T i = T(0); i < num_rows; i++)
	{
		auto j = j_end;
		while (j > j_start)
		{
			shared_ptr<Node<T>> new_element = make_shared<Node<T>>(*j);
			new_element->row_next = row_start;
			row_start = new_element;
			j--;
			if (new_element->row_next == nullptr) connect_row = new_element;
		}
		connect_row->row_next = row_start;
		if (i == T(0))
		{
			head = row_start;
			track_head = head;
		}
		else
		{
			head->col_next = row_start;
			shared_ptr<Node<T>> makeconn1 = head->row_next;
			shared_ptr<Node<T>> makeconn2 = row_start->row_next;
			while (makeconn1 != head)
			{
				makeconn1->col_next = makeconn2;
				makeconn1 = makeconn1->row_next;
				makeconn2 = makeconn2->row_next;
			}
			head = head->col_next;
		}
		j_start = j_end;
		j_end = j_end + num_columns;
		if (i < num_rows - 1) row_start.reset();
	}
	head = track_head;
	row_start->col_next = head;
	if (head->row_next != head)
	{
		shared_ptr<Node<T>> make_connection = head->row_next;
		connect_col = row_start->row_next;
		while (make_connection != head)
		{
			connect_col->col_next = make_connection;
			make_connection = make_connection->row_next;
			connect_col = connect_col->row_next;
		}
	}
	cout << "Initializer List" << endl;
}

template <class T> Ring2D<T> :: ~Ring2D()
{
	if (!head)
	{
		cout << "Destructor" << endl;
		return;
	}
	if (head->row_next != head)
	{
		shared_ptr<Node<T>> del_point1 = head->row_next;
		shared_ptr<Node<T>> del_point2;
		while (del_point1 != head)
		{
			del_point2 = del_point1->row_next;
			del_point1->col_next.reset();
			del_point1.reset();
			del_point1 = del_point2;
		}
		del_point2 = head->col_next;
		while (del_point2 != head)
		{
			del_point2->row_next.reset();
			del_point2 = del_point2->col_next;
		}
		del_point2.reset();
		cout << "Destructor" << endl;
	}
	else
	{
		head->row_next.reset();
		head->col_next.reset();
		cout << "Destructor" << endl;
	}
}

template<class T> Ring2D<T>::Ring2D(const Ring2D<T>& R)
{
	if (!R.head)
	{
		cout << "Copy Constructor" << endl;
		return;
	}
	shared_ptr<Node<T>> create_ring = R.head->row_next;
	shared_ptr<Node<T>> row_start;
	shared_ptr<Node<T>> row_connect;
	shared_ptr<Node<T>> new_head = make_shared<Node<T>>();
	while (create_ring != R.head)
	{
		shared_ptr<Node<T>> new_element = make_shared<Node<T>>();
		new_element->row_next = row_start;
		row_start = new_element;
		if (new_element->row_next == nullptr) row_connect = new_element;
		create_ring = create_ring->row_next;
	}
	if (row_start != nullptr)
	{
		new_head->row_next = row_start;
		row_connect->row_next = new_head;
		head = new_head;
	}
	else
	{
		new_head->row_next = new_head;
		head = new_head;
	}
	shared_ptr<Node<T>> track_head = head;
	if (R.head->col_next != R.head)
	{
		create_ring = R.head->col_next;
		row_connect.reset();
		while (create_ring != R.head)
		{
			row_start.reset();
			shared_ptr<Node<T>> new_rows = make_shared<Node<T>>();
			shared_ptr<Node<T>> create_row = create_ring->row_next;
			while (create_row != create_ring)
			{
				shared_ptr<Node<T>> new_element = make_shared<Node<T>>();
				new_element->row_next = row_start;
				row_start = new_element;
				if (new_element->row_next == nullptr) row_connect = new_element;
				create_row = create_row->row_next;
			}
			if (row_start != nullptr)
			{
				new_rows->row_next = row_start;
				row_connect->row_next = new_rows;
			}
			else new_rows->row_next = new_rows;
			track_head->col_next = new_rows;
			shared_ptr<Node<T>> conn_up = track_head->row_next;
			shared_ptr<Node<T>> conn_down = new_rows->row_next;
			while (conn_up != track_head)
			{
				conn_up->col_next = conn_down;
				conn_up = conn_up->row_next;
				conn_down = conn_down->row_next;
			}
			track_head = track_head->col_next;
			create_ring = create_ring->col_next;
		}
	}
	track_head->col_next = head;
	create_ring.reset();
	create_ring = head->row_next;
	track_head = track_head->row_next;
	while (create_ring != head)
	{
		track_head->col_next = create_ring;
		track_head = track_head->row_next;
		create_ring = create_ring->row_next;
	}
	create_ring = R.head->row_next;
	new_head = head->row_next;
	row_start.reset();
	row_connect.reset();
	head->pValue = make_shared<T>(*(R.head->pValue));
	while (new_head != head)
	{
		new_head->pValue = make_shared<T>(*(create_ring->pValue));
		new_head = new_head->row_next;
		create_ring = create_ring->row_next;
	}
	if (new_head->col_next != head)
	{
		new_head = new_head->col_next;
		create_ring = create_ring->col_next;
		while (new_head != head)
		{
			new_head->pValue = make_shared<T>(*(create_ring->pValue));
			row_start = new_head->row_next;
			create_ring = create_ring->row_next;
			while (row_start != new_head)
			{
				row_start->pValue = make_shared<T>(*(create_ring->pValue));
				row_start = row_start->row_next;
				create_ring = create_ring->row_next;
			}
			new_head = new_head->col_next;
			create_ring = create_ring->col_next;
		}
	}
	cout << "Copy Constructor" << endl;
}

template<class T> void Ring2D<T>::operator=(const Ring2D<T>& R)
{
	if (head)
	{
		if (head->row_next != head)
		{
			shared_ptr<Node<T>> del_point1 = head->row_next;
			shared_ptr<Node<T>> del_point2;
			while (del_point1 != head)
			{
				del_point2 = del_point1->row_next;
				del_point1->col_next.reset();
				del_point1.reset();
				del_point1 = del_point2;
			}
			del_point2 = head->col_next;
			while (del_point2 != head)
			{
				del_point2->row_next.reset();
				del_point2 = del_point2->col_next;
			}
			del_point2.reset();
			head.reset();
		}
		else
		{
			head->row_next.reset();
			head->col_next.reset();
			head.reset();
		}
	}
	if (!R.head)
	{
		cout << "Copy Assignment" << endl;
		return;
	}
	shared_ptr<Node<T>> create_ring = R.head->row_next;
	shared_ptr<Node<T>> row_start;
	shared_ptr<Node<T>> row_connect;
	shared_ptr<Node<T>> new_head = make_shared<Node<T>>();
	while (create_ring != R.head)
	{
		shared_ptr<Node<T>> new_element = make_shared<Node<T>>();
		new_element->row_next = row_start;
		row_start = new_element;
		if (new_element->row_next == nullptr) row_connect = new_element;
		create_ring = create_ring->row_next;
	}
	if (row_start != nullptr)
	{
		new_head->row_next = row_start;
		row_connect->row_next = new_head;
		head = new_head;
	}
	else
	{
		new_head->row_next = new_head;
		head = new_head;
	}
	shared_ptr<Node<T>> track_head = head;
	if (R.head->col_next != R.head)
	{
		create_ring = R.head->col_next;
		row_connect.reset();
		while (create_ring != R.head)
		{
			row_start.reset();
			shared_ptr<Node<T>> new_rows = make_shared<Node<T>>();
			shared_ptr<Node<T>> create_row = create_ring->row_next;
			while (create_row != create_ring)
			{
				shared_ptr<Node<T>> new_element = make_shared<Node<T>>();
				new_element->row_next = row_start;
				row_start = new_element;
				if (new_element->row_next == nullptr) row_connect = new_element;
				create_row = create_row->row_next;
			}
			if (row_start != nullptr)
			{
				new_rows->row_next = row_start;
				row_connect->row_next = new_rows;
			}
			else new_rows->row_next = new_rows;
			track_head->col_next = new_rows;
			shared_ptr<Node<T>> conn_up = track_head->row_next;
			shared_ptr<Node<T>> conn_down = new_rows->row_next;
			while (conn_up != track_head)
			{
				conn_up->col_next = conn_down;
				conn_up = conn_up->row_next;
				conn_down = conn_down->row_next;
			}
			track_head = track_head->col_next;
			create_ring = create_ring->col_next;
		}
	}
	track_head->col_next = head;
	create_ring.reset();
	create_ring = head->row_next;
	track_head = track_head->row_next;
	while (create_ring != head)
	{
		track_head->col_next = create_ring;
		track_head = track_head->row_next;
		create_ring = create_ring->row_next;
	}
	create_ring = R.head->row_next;
	new_head = head->row_next;
	row_start.reset();
	row_connect.reset();
	head->pValue = make_shared<T>(*(R.head->pValue));
	while (new_head != head)
	{
		new_head->pValue = make_shared<T>(*(create_ring->pValue));
		new_head = new_head->row_next;
		create_ring = create_ring->row_next;
	}
	if (new_head->col_next != head)
	{
		new_head = new_head->col_next;
		create_ring = create_ring->col_next;
		while (new_head != head)
		{
			new_head->pValue = make_shared<T>(*(create_ring->pValue));
			row_start = new_head->row_next;
			create_ring = create_ring->row_next;
			while (row_start != new_head)
			{
				row_start->pValue = make_shared<T>(*(create_ring->pValue));
				row_start = row_start->row_next;
				create_ring = create_ring->row_next;
			}
			new_head = new_head->col_next;
			create_ring = create_ring->col_next;
		}
	}
	cout << "Copy Assignment" << endl;
}

template <class T> Ring2D<T>::Ring2D(Ring2D<T>&& R)
{
	head = R.head;
	R.head.reset();
	cout << "Move Constructor" << endl;
}

template <class T> void Ring2D<T>::operator=(Ring2D<T>&& R)
{
	if (head)
	{
		if (head->row_next != head)
		{
			shared_ptr<Node<T>> del_point1 = head->row_next;
			shared_ptr<Node<T>> del_point2;
			while (del_point1 != head)
			{
				del_point2 = del_point1->row_next;
				del_point1->col_next.reset();
				del_point1.reset();
				del_point1 = del_point2;
			}
			del_point2 = head->col_next;
			while (del_point2 != head)
			{
				del_point2->row_next.reset();
				del_point2 = del_point2->col_next;
			}
			del_point2.reset();
			head.reset();
		}
		else
		{
			head->row_next.reset();
			head->col_next.reset();
			head.reset();
		}
	}
	head = R.head;
	R.head.reset();
	cout << "Move Assignment" << endl;
}

template <class T> Ring2D<T> Ring2D<T>::ThreeTimes()
{
	Ring2D<T> threet{ *this };
	if (!threet.head) return threet;
	shared_ptr<Node<T>> track = threet.head;
	*(track->pValue) *= 3;
	shared_ptr<Node<T>> rowmult = track->row_next;
	while (rowmult != track)
	{
		*(rowmult->pValue) *= 3;
		rowmult = rowmult->row_next;
	}
	track = track->col_next;
	while (track != threet.head)
	{
		*(track->pValue) *= 3;
		rowmult = track->row_next;
		while (rowmult != track)
		{
			*(rowmult->pValue) *= 3;
			rowmult = rowmult->row_next;
		}
		track = track->col_next;
	}
	return threet;
}

template <class T> void Ring2D<T> ::DeleteRow(int r)
{
	shared_ptr<Node<T>> find_r = head;
	if (!head || r < 1) return;
	else
	{
		while (r > 1)
		{
			if (find_r->col_next == head) return;
			find_r = find_r->col_next;
			--r;
		}
	}
	if (find_r->col_next != find_r)
	{
		shared_ptr<Node<T>> conn_r = head;
		while (conn_r->col_next != find_r) conn_r = conn_r->col_next;
		conn_r->col_next = find_r->col_next;
		shared_ptr<Node<T>> conn_del = conn_r->row_next;
		shared_ptr<Node<T>> find_del = find_r->row_next;
		while (conn_del != conn_r)
		{
			conn_del->col_next = find_del->col_next;
			conn_del = conn_del->row_next;
			find_del = find_del->row_next;
		}
	}
	else
	{
		shared_ptr<Node<T>> conn_del = find_r->row_next;
		find_r->col_next.reset();
		while (conn_del != find_r)
		{
			conn_del->col_next.reset();
			conn_del = conn_del->row_next;
		}
		head.reset();
	}
	if (find_r == head && find_r->col_next) head = find_r->col_next;
	find_r->row_next.reset();
	find_r.reset();
}

template <class T> ostream& operator<<(ostream& str, const Ring2D<T>& R)
{
	if (!R.head) str << "";
	else
	{
		str << *(R.head->pValue) << " ";
		if (R.head->row_next != R.head || (R.head->col_next != R.head))
		{
			shared_ptr<Node<T>> first_r = R.head->row_next;
			while (first_r != R.head)
			{
				str << *(first_r->pValue) << " ";
				first_r = first_r->row_next;
			}
			str << endl;
			if (R.head->col_next != R.head)
			{
				shared_ptr<Node<T>> check_col = R.head->col_next;
				while (check_col != R.head)
				{
					str << *(check_col->pValue) << " ";
					shared_ptr<Node<T>> print_r = check_col->row_next;
					while (print_r != check_col)
					{
						str << *(print_r->pValue) << " ";
						print_r = print_r->row_next;
					}
					str << endl;
					check_col = check_col->col_next;
				}
			}
		}
	}
	return str;
}

int main() {
	Ring2D<int> R1{ 3, 4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };//initializer_list
	cout << R1 << endl << endl;


	Ring2D<int> R2{ R1 };//copy constructor
	cout << R2 << endl << endl;


	Ring2D<int> R3;
	R3 = R1;//copy assignment
	cout << R3 << endl << endl;

	Ring2D<int> R4;
	R4 = R1.ThreeTimes();//this is pointing to object R1
	//Compiler will convert it to R4.operator=(R1.ThreeTimes());
	//copy constructor -- declare temp and initialize it to R1
	//move constructor -- create hidden (temporary) copy
	//destructor-- delete temp becuase it goes out of scope
	//move assignment -- Assign value from hidden copy to R4
	//destructor-- delete hedden copy because it goes out of scope
	cout << R4 << endl << endl;


	R4.DeleteRow(2);
	cout << R4 << endl << endl;
	R4.DeleteRow(2);
	cout << R4 << endl << endl;
	R4.DeleteRow(1);
	cout << R4 << endl << endl;

	return 0;
}





