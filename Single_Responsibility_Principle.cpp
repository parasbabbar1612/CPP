#include<iostream> 
#include<vector>
#include<string>
#include<fstream>

/* This is an example of single-responsibility class where Journal class responsiblity is just limited to creating journal
and adding entries to the journal.To save the contents of the journal, we created another class journal_operations to save the journal entries to 
database.
*/

using namespace std;

class Journal {
public:
	string journal_name;
	vector<string> entries;
	Journal(){}
	Journal(const string& temp_name) :journal_name(temp_name) {};
	void add_entries(const string& entry);
};

void Journal::add_entries(const string& entry) {
	static int count_entries = 1;
	entries.push_back(to_string(count_entries++) +": " +entry);
}

class journal_operations {
public:
	void save_to_file(const string &file_name, Journal j) {
		ofstream o1(file_name);
		for (auto curr_entry : j.entries) {
			o1 << curr_entry << endl;
		}
	}
};

int main() {
	Journal journal1("Day1");
	journal1.add_entries("On the day of 9/14/2020 i discovered design patterns course.");
	journal1.add_entries("This is my first program.");
	journal_operations db1;
	db1.save_to_file("Journal1.txt", journal1);
	return 0;
}