//HW3 by Paras Babbar
//SU Net ID:pbabbar SUID:418085055
//Due: 11:59PM, February 21 (Friday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include<iomanip>
#include<tuple>

using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

	//You might need to implement some overloaded operators here.

};
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc. 

void add_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);
void remove_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);
void add_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																//All courses in the list should be sorted according to name (increasing order)
void drop_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id);
void print_student_all_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;
template<class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2*>& m1)
{
	str << "DB:"<<endl;
	for (auto i : m1)
	{
		str << "ID: " << i.first << endl;
		if (i.second == nullptr) str << "NULL" << " ";
		else 
		{
			str << "Overall GPA: " << setprecision(2) << fixed << get<1>(*(i.second)) << endl;
			str << "Overall Credits: " << get<0>(*(i.second)) << endl;
			if (get<2>((*(i.second))) == nullptr) str << "NULL" << " ";
			else str << *(get<2>(*(i.second)));
		}
			
	}
	return str;

}

template<class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2>& m1)
{
	for (auto i : m1)
	{
		str << "Semester: " << i.first << endl;
		str << i.second ;
	}
	return str;
}

template<typename T1, typename T2, typename T3> ostream& operator<<(ostream& str, const tuple<T1, T2, T3*>& t)
{
	str << "GPA: " << setprecision(2) << fixed << get<1>(t) << endl;
	str << "Credits: " << get<0>(t) << endl;
	if (get<2>(t) == nullptr) str << "NULL" << " ";
	else str << *(get<2>(t)) << " " << endl;
	return str;
}

template<typename T1, typename T2, typename T3> ostream& operator<<(ostream& str, tuple<T1, T2, list<course*>*>& t)
{
	str << "GPA: " << setprecision(2) << fixed << get<1>(t) << endl;
	str << "Credits: " << get<0>(t) << endl;
	if (get<2>(t) == nullptr) str << "NULL" << " ";
	else str << (get<2>(t));
	return str;
}


template<class T> ostream& operator<<(ostream& str, const list<T*>& l)
{
	if (l.size() == 0) str << "{NULL}";
	for (auto i : l)
	{
		if (i == nullptr) str << "NULL" << " ";
		else str << *i << " ";
	}
	return str;
}

template<class T> ostream& operator<<(ostream& str, list<T*>* l)
{
	if (l == nullptr) str << "{NULL}";
	for (auto i : *l)
	{
		if (i == nullptr) str << "NULL" << " ";
		else str << *i << " ";
	}
	return str;
}

ostream& operator<<(ostream& str, const course& c)
{
	str << "(";
	for (auto i : c.name) str << i;
	str << " " << c.section << " " << c.credits << " ";
	for (auto i : c.grade) str << i;
	str << ")";
	return str;

}

//You might need to implement some overloaded operators in the course class.

int main() {
	map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>  DB;

	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);
	
	drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111); //sorted according to course name
	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111);//ID GPA
	
	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);
	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;

	getchar();
	getchar();
	return 0;
}

void add_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
	if (DB.size() == 0)
	{
		tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>* newt = new tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>();
		get<0>(*(newt)) = 0;
		get<1>(*(newt)) = 0.00;
		get<2>(*(newt)) = nullptr;
		DB[id] = newt;
	}
	else
	{
		auto it = DB.find(id);
		if (it == DB.end())
		{
			tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>* newt = new tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>();
			get<0>(*(newt)) = 0;
			get<1>(*(newt)) = 0.00;
			get<2>(*(newt)) = nullptr;
			DB[id] = newt;
		}
	}
}

void remove_student(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
	if (DB.size() == 0) return;
	auto it = DB.find(id);
	if (it != DB.end())
	{
		tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>* delt = it->second;
		if (get<2>(*(delt)) == nullptr)
		{
			delete delt;
			DB.erase(it);
		}
		else
		{
			map<int, tuple<int, float, list<course*>*>>* delm = get<2>(*(delt));
			for (auto it1 = (*delm).begin(); it1 != (*delm).end(); it1++)
			{
				list<course*>* 
				dell = get<2>(it1->second);
				for(auto i:*dell)
				{
					course* c = i;
					delete c;
				}
				(*dell).clear();
				delete dell;
				if (it1 == (*delm).end()) break;
			}
		(*delm).clear();
		delete delm;
		delete delt;
		DB.erase(it);
	    }
	}
}


void add_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {
	float calgp;
	if (c.grade.compare("A") == 0) calgp = 4.0;
	else if (c.grade.compare("A-") == 0) calgp = 3.6666;
	else if (c.grade.compare("B+") == 0) calgp = 3.3333;
	else if (c.grade.compare("B") == 0) calgp = 3.0;
	else if (c.grade.compare("B-") == 0) calgp = 2.6666;
	else if (c.grade.compare("C+") == 0) calgp = 2.3333;
	else if (c.grade.compare("C") == 0) calgp = 2.0;
	else if (c.grade.compare("C-") == 0) calgp = 1.6666;
	else if (c.grade.compare("D") == 0) calgp = 1.0;
	else if (c.grade.compare("D-") == 0) calgp = 0.6666;
	else if (c.grade.compare("F") == 0) calgp = 0;

	auto it = DB.find(id);
	if (it != DB.end())
	{
		if (get<2>(*(it->second)) == nullptr)
		{
			auto &i = get<2>(*(it->second));
			i = new map<int, tuple<int, float, list<course*>*>>();
			course* newc = new course(c);
			list<course*>* l1 = new list<course*>();
			(*(l1)).push_back(newc);
			tuple<int, float, list<course*>*> newtuple = make_tuple(c.credits, calgp, l1);
			(*(i))[semester] = newtuple;
			get<0>(*(it->second)) = c.credits;
			get<1>(*(it->second)) = calgp;
			get<2>(*(it->second)) = i;
		}
		else
		{
			get<0>(*(it->second)) += c.credits;
			auto &i = get<2>(*(it->second));
			auto it1 = (*(i)).find(semester);
			if (it1 != (*(i)).end())
			{
				get<0>(it1->second) += c.credits;
				course* newc = new course(c);
				list<course*>* l1 = get<2>(it1->second);
				list<course*> ::iterator it2;
				for (it2 = (*(l1)).begin(); it2 != (*(l1)).end(); it2++)
				{
					if (c.name < (*(*it2)).name)
					{
						(*(l1)).insert(it2, newc);
						float currgpa = get<1>(it1->second);
						float currcredits = float(get<0>(it1->second));
						float totalpoints = currgpa * (currcredits - c.credits);
						totalpoints += calgp * c.credits;
						get<1>(it1->second) = totalpoints / currcredits;
						currgpa = get<1>(*(it->second));
						currcredits = float(get<0>(*(it->second)));
						totalpoints = currgpa * (currcredits - c.credits);
						totalpoints += calgp * c.credits;
						get<1>(*(it->second)) = totalpoints / currcredits;

						break;
					}
					if (c.name == (*(*it2)).name)
					{
						delete newc;
						get<0>(it1->second) -= c.credits;
						get<0>(*(it->second)) -= c.credits;
						break;
					}
				}
				if (it2 == (*(l1)).end())
				{
					(*(l1)).push_back(newc);
					float currgpa = get<1>(it1->second);
					float currcredits = float(get<0>(it1->second));
					float totalpoints = currgpa * (currcredits - c.credits);
					totalpoints += calgp * c.credits;
					get<1>(it1->second) = totalpoints / currcredits;
					currgpa = get<1>(*(it->second));
					currcredits = float(get<0>(*(it->second)));
					totalpoints = currgpa * (currcredits - c.credits);
					totalpoints += calgp * c.credits;
					get<1>(*(it->second)) = totalpoints / currcredits;
				}

			}
			else
			{
				course* newc = new course(c);
				list<course*>* l1 = new list<course*>();
				(*(l1)).push_back(newc);
				tuple<int, float, list<course*>*> newtuple = make_tuple(c.credits, calgp, l1);
				(*(i))[semester] = newtuple;
				float currgpa = get<1>(*(it->second));
				float currcredits = float(get<0>(*(it->second)));
				float totalpoints = currgpa * (currcredits - c.credits);
				totalpoints += calgp * c.credits;
				get<1>(*(it->second)) = totalpoints / currcredits;

			}
		}
	}
}

void drop_course(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id, course c) {
	float calgp;
	if (c.grade.compare("A") == 0) calgp = 4.0;
	else if (c.grade.compare("A-") == 0) calgp = 3.6666;
	else if (c.grade.compare("B+") == 0) calgp = 3.3333;
	else if (c.grade.compare("B") == 0) calgp = 3.0;
	else if (c.grade.compare("B-") == 0) calgp = 2.6666;
	else if (c.grade.compare("C+") == 0) calgp = 2.3333;
	else if (c.grade.compare("C") == 0) calgp = 2.0;
	else if (c.grade.compare("C-") == 0) calgp = 1.6666;
	else if (c.grade.compare("D") == 0) calgp = 1.0;
	else if (c.grade.compare("D-") == 0) calgp = 0.6666;
	else if (c.grade.compare("F") == 0) calgp = 0;

	auto it = DB.find(id);
	if (it != DB.end())
	{
		if (get<2>(*(it->second)) != nullptr)
		{
			auto it1 = (*(get<2>(*(it->second)))).find(semester);
			if (it1 != (*(get<2>(*(it->second)))).end())
			{
				list<course*>* dell = get<2>(it1->second);
				for (auto it2 = (*dell).begin(); it2 != (*dell).end(); it2++)
				{
					if (c.name == (*(*it2)).name)
					{
						course* delc = *it2;
						(*(dell)).erase(it2);
						delete delc;
						float currgpa = get<1>(it1->second);
						float currcredits = float(get<0>(it1->second));
						float totalpoints = currgpa * currcredits;
						totalpoints -= float(calgp * c.credits);
						get<1>(it1->second) = totalpoints / (currcredits - c.credits);
						currgpa = get<1>(*(it->second));
						currcredits = float(get<0>(*(it->second)));
						totalpoints = currgpa * currcredits;
						totalpoints -= float(calgp * c.credits);
                        get<1>(*(it->second)) = totalpoints / (currcredits - c.credits);
						get<0>(*(it->second)) -= c.credits;
						get<0>((it1->second)) -= c.credits;
						break;
					}
				}
			}
		}

	}
}

void print_student_semester_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int semester, int id) {
	auto it = DB.find(id);
	if (it != DB.end())
	{
		if (get<2>(*(it->second)) != nullptr)
		{
			auto &i = get<2>(*(it->second));
			auto it1 = (*(i)).find(semester);
			if (it1 != (*(i)).end())
			{
				cout << "ID: " << it->first << endl;
				cout << "Semester: " << it1->first << endl;
				cout << "GPA: " << setprecision(2) << fixed << get<1>(it1->second) << endl;
				cout << "Credits: " << get<0>(it1->second) << endl;
				cout << get<2>(it1->second) << endl;
				cout << endl;
			}
		}
		else
		{
			cout << DB << endl;
		}
	}
}
void print_student_all_courses(map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>*>& DB, int id) {
	if (DB.size() == 0) return;
	auto it = DB.find(id);
	if (it != DB.end())
	{
		cout << "ID: " << id << endl;
		cout << "Overall GPA: "<<setprecision(2)<<fixed<<get<1>(*(it->second)) << endl;
		cout << "Overall Credits: " << get<0>(*(it->second)) << endl;
		map<int, tuple<int, float, list<course*>*>>* outm = get<2>(*(it->second));
		cout << *outm<<endl;
	}
}


