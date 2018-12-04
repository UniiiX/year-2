#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>

using namespace std;

string isPalindrom(string);
string longestString(string first, string second, string third);

int main() {
	string s = "aacabacg";
	string s1 = "abaca";
	string s2 = "caccsc";
	string s3 = "aabbcbbaa";
	string s4 = "qwertyuiopasdfghj";
	string s5 = "abracadabra";

	cout << s5 << ":  " << isPalindrom(s5);
	cout << endl;
	cout << s4 << ":  " << isPalindrom(s4);
	cout << endl;
	cout << s3 << ":  " << isPalindrom(s3);
	cout << endl;
	cout << s2 << ":  " << isPalindrom(s2);
	cout << endl;
	cout << s << ":  " << isPalindrom(s);
	return 0;
}

string longestString(string first, string second) {
	string max = "";
	if (first.size() >= second.size())
		max = first;
	else
		max = second;

	return max;
}

string isPalindrom(string s) {
	if (s.size() <= 1)
		return s;
	else if (s[0] == s[s.size() - 1])
		return s[0] + isPalindrom(s.substr(1, s.size() - 2)) + s[0];
	else
    {
        string substr1 = isPalindrom(s.substr(0, s.size() - 1));
        string substr2 = isPalindrom(s.substr(1, s.size() - 1));
        return(longestString(substr1, substr2));
    }
}
