#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>

using namespace std;

bool boyermoore(string tex, string ser)
{
	if(ser.length()>tex.length()) return false;
	int size = ser.length();
	unordered_map<char, int> inc;
	for (int i = 0; i < size; i++)
	{
		inc[ser[i]] = max(1, size - i - 1);
	}
	inc.insert({ '*', size });
	int check = size - 1;
	int point = check;
	while (point <= tex.size() - 1)
	{
		if (ser[check] == tex[point])
		{
			int i = check;
			int j = point;
			while (i >= 0 && ser[i] == tex[j])
			{
				--i;
				--j;
			}
			if (i == -1) return true;
			else
			{
				if (!inc[tex[j]]) point = j + inc['*'];
				else point = j + inc[tex[j]];
			}
		}
		else if (ser[check] != tex[point] && (!inc[tex[point]])) point += inc['*'];
		else point += inc[tex[point]];
	}
	return false;
}

int main()
{

	string tex = "";
	string ser = "";
	cout << "Enter text" << endl;
	getline(cin,tex);
	cout << "Enter search word" << endl;
	getline(cin, ser);
	int result = boyermoore(tex, ser);
	if (result == 1) cout << "Found";
	else cout << "Not Found";
	return 0;
}