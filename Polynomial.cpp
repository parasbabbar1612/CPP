#include<iostream>
#include<vector>

using namespace std;

class val {
public:
	int coefficient;
	int power;
	val(){}
	val(int c, int p) :coefficient(c), power(p) {};
};

class equation {
public:
	int num;
	vector<val> expression;
	equation(){}
	void display();
	void create();
	int evaluate(int x);
	equation add(equation e);
};

void equation::display() {
	for (int i = 0; i < this->num; i++) {
		if (i != 0) {
			cout << " + " << this->expression[i].coefficient << "x ^" << this->expression[i].power;
		}
		else {
			cout <<this->expression[i].coefficient << "x ^" << this->expression[i].power;
		}
	}
	cout << endl;
}

void equation::create() {
	cout << "Enter number of non-zero elements";
	cin >> num;
	int c, p;
	cout << "Enter the values(coefficient & power) in the expression" << endl;
	for (int i = 0; i < num; i++) {
		cin >> c >> p;
		val v(c, p);
		expression.emplace_back(v);
	}
	display();
}

equation equation::add(equation e) {
	equation answer;
	int p1 = 0, p2 = 0;
	while (p1 < this->expression.size() && p2 < e.expression.size()) {
		if (this->expression[p1].power > e.expression[p2].power) {
			val temp(this->expression[p1].coefficient, this->expression[p1].power);
			answer.expression.emplace_back(temp);
			++p1;
		}
		else if (this->expression[p1].power < e.expression[p2].power) {
			val temp(e.expression[p2].coefficient, e.expression[p2].power);
			answer.expression.emplace_back(temp);
			++p2;
		}
		else {
			val temp(e.expression[p2].coefficient + this->expression[p1].coefficient, e.expression[p2].power);
			answer.expression.emplace_back(temp);
			++p1;
			++p2;
		}
	}
	while (p1 < this->expression.size()) {
		val temp(this->expression[p1].coefficient, this->expression[p1].power);
		answer.expression.emplace_back(temp);
		++p1;
	}
	while (p2 < e.expression.size()) {
		val temp(e.expression[p2].coefficient, e.expression[p2].power);
		answer.expression.emplace_back(temp);
		++p2;
	}
	answer.num = answer.expression.size();
	return answer;
}

int equation::evaluate(int x)
{
	int answer = 0;
	for (int i = 0; i < this->num; i++) {
		answer += this->expression[i].coefficient * (pow(x, this->expression[i].power));
	}
	return answer;
}

int main() {
	equation e1, e2;
	e1.create();
	e2.create();
	equation e3=e1.add(e2);
	e3.display();
	cout << e1.evaluate(5) << endl;
	cout << e2.evaluate(6) << endl;
	cout << e1.evaluate(10) << endl;
	return 0;
}