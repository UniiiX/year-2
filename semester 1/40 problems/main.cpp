#include <iostream>
#include <string>

using namespace std;

const int lettersCount = 52; //there are 26 letters in English alphabet; multiplying by 2 to include upper case

void InputString(string &str)
{
    cout << "Input string: ";
    getline(cin, str);
}

int* CountLetters(string str)
{
    int* result = new int[lettersCount];
    for (int i = 0; i < lettersCount; i++)
    {
        result[i] = 0;
    }
    for (int i = 0; i < str.size(); i++)
    {
        int index = str.at(i) - 'a';
        if (0 <= index || index < 26)
        {
            result[index]++;
            continue;
        }
        index = str.at(i) - 'A';
        if (0 <= index || index < 26)
        {
            result[index]++;
        }
    }
    return result;
}

int main()
{
    string firstString;
    string secondString;
    InputString(firstString);
    InputString(secondString);
    int* countOfLettersInFirstString = CountLetters(firstString);
    int* countOfLettersInSecondString = CountLetters(secondString);
    int* countOfLettersInMaxSubstring = new int[lettersCount];
    cout << "Maximal Substring is: ";
    for (int i = 0; i < lettersCount; i++)
    {
        countOfLettersInMaxSubstring[i] = min(countOfLettersInFirstString[i], countOfLettersInSecondString[i]);
        for (int j = 0; j < countOfLettersInMaxSubstring[i]; j++)
        {
            cout << char('a' + i);
        }
    }
    return 0;
}
