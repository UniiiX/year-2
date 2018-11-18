#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

template<class T>
vector<int> PrefixFunction(const T& pattern)
{
    int size = pattern.size();
    vector<int> result(size, 0);

    int k = 0;
	for (int i = 1; i < size; i++)
    {
		while ((k > 0) && (pattern[k] != pattern[i]))
		{
            k = result[k - 1];
		}
		if (pattern[k] == pattern[i])
        {
            k++;
        }
		result[i] = k;
	}

    return result;
}

template<class T>
vector<int> KMPSearch(const T& pattern, const T& text)
{
    vector<int> prefixFunction = PrefixFunction(pattern);
    int patternSize = pattern.size();
    int textSize = text.size();
    vector<int> result;
    result.reserve(textSize);

    int k = 0;
    for (int i = 0; i < textSize; i++)
    {
        while (k > 0 && pattern[k] != text[i])
        {
            k = prefixFunction[k - 1];
        }
        if (pattern[k] == text[i])
        {
            k++;
        }
        if (k == patternSize)
        {
            result.push_back(i - patternSize + 1);
        }
    }
    return result;
}

int main()
{
    string str1, str2;
    cin >> str1;
    cin >> str2;
    string str(str2 + str2);
    vector<int> shift = KMPSearch(str1, str);
    if (!shift.empty())
    {
        cout << "First string is the cyclic shift of the second string" << endl;
        cout << "Shift is: " << shift.at(0) << endl;
    }
    else
    {
        cout << "First string is not the cyclic shift of the second string" << endl;
    }
}
