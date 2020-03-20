#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

template<class T> class dim
{
public:
	T a, b, c;
	dim() :a{ 0 }, b{ 0 }, c{ 0 }{}
	dim(T x,T y,T z):a{x},b{y},c{z}{}
	T getvol()const { return a * b * c; }
	T sarea() const { return 2 * (a * b + b * c + a * c); }
};

template<class T> ostream& operator<<(ostream &str, const dim<T> &d1) 
{
	str << "[" << d1.a << "," << d1.b << "," << d1.c << "]";
	return str;
}

template <class T> class my_compare {
public:
	template <class T> bool operator()(const dim<T> &d1, const dim<T> &d2) const
	{
		return d1.getvol() < d2.getvol();
	}
};

template <class T> class my_hash
{
public:
	size_t operator()(const dim<T> &d1) const
	{
		hash<int> h;
		return h(d1.sarea() * d1.getvol());
	}
};

template <class T> class my_equal_to
{
public:
	bool operator()(const dim<T> &d1, const dim<T> &d2) const
	{
		return d1.sarea()==d2.sarea();
	}
};


int main()
{
	my_compare<int> f1;
	dim<int> d1(10, 15, 20);
	dim<int> d2(11, 11, 25);
	cout << f1(d1, d2)<<endl;
	dim<int> d3(20, 6, 14);
	dim<int> d4(15, 18, 29);
	unordered_map<dim<int>, int, my_hash<int>, my_equal_to<int>> m1;
	m1.insert({ d1,100 });
	m1.insert({ d2,200 });
	m1.insert({ d3,400 });
	m1.insert({ d4,500 });
	for (auto i : m1) cout << i.first << " " << i.second << endl;
	return 0;
}