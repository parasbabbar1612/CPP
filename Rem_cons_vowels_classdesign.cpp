#include<iostream>
#include<string>

using namespace std;

class input_string {
	string input;
public:
	void get_input() {
		cout << "Enter the string" << endl;
		getline(cin, input, '\n');
	}
	string get_string() {
		return input;
	}
};


class operations {
public:
	virtual string operation(const string &s) = 0;
};

class rem_vowels :public operations {
public:
	string operation(const string& s) {
		string answer = "";
		string valid = "AEIOUaeiou";
		for (auto i : s) {
			if (valid.find(i) != string::npos || i == ' ') answer += i;
		}
		return answer;
	}
};

class rem_consonants :public operations {
public:
	string operation(const string& s) {
		string answer = "";
		string valid = "AEIOUaeiou";
		for (auto i : s) {
			if (valid.find(i) == string::npos || i==' ') answer += i;
		}
		return answer;
	}
};

class output_string {
public:
	void output_without_vowels(const string& s) {
		cout << "String without vowels is -> ";
		for (auto ch : s) {
			cout << ch;
		}
		cout << endl;
	}
	void output_without_consonants(const string& s) {
		cout << "String without consonants is -> ";
		for (auto ch : s) {
			cout << ch;
		}
		cout << endl;

	}
};


class base_string {
	string input;
	rem_vowels rv;
	rem_consonants rc;
	input_string in_ob;
	output_string out_ob;
public:
	base_string() {
		in_ob.get_input();
		input = in_ob.get_string();
		
	}
	base_string(string s) {
		input = s;
	}
	void perform_operations();
};

void base_string::perform_operations() {
	string without_vowels = rv.operation(input);
	string without_consonants = rc.operation(input);
	out_ob.output_without_vowels(without_vowels);
	out_ob.output_without_consonants(without_consonants);
}

int main() {
	base_string b("Paras");
	b.perform_operations();
	return 0;
}