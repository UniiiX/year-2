#include <iostream>
#include <vector>

using namespace std;

int RabinKarpSearch (string text, string pattern)
{
    const int textLength = text.size();
    const int patternLength = pattern.size();
    const int radix = 31;
    vector<long long> radixPowers(max (patternLength, textLength));
    radixPowers[0] = 1;
    for (int i = 1; i < radixPowers.size(); ++i)
    {
        radixPowers[i] = radixPowers[i - 1] * radix;
    }

    vector<long long> hashFunction (textLength);
    for (int i = 0; i < textLength; ++i)
    {
        hashFunction[i] = (text[i] - 'a' + 1) * radixPowers[i];
        if (i != 0)
        {
            hashFunction[i] += hashFunction[i - 1];
        }
    }

    long long key = 0;
    for (int i = 0; i < patternLength; ++i)
    {
        key += (pattern[i] - 'a' + 1) * radixPowers[i];
    }

    for (int i = 0; i + patternLength - 1 < textLength; ++i)
    {
        long long currrentValue = hashFunction[i + patternLength - 1];
        if (i != 0)
        {
            currrentValue -= hashFunction[i - 1];
        }

        if (currrentValue == key * radixPowers[i])
        {
            cout << "Pattern was found in the text. Position: " << i + 1 << endl;
            return i + 1;
        }
    }
    cout << "Pattern was not found in the text." << endl;
    return -1;
}

void RabinKarpSearch2D(string* text, string* pattern)
{
    const int textLength = text[0].size();
    const int patternLength = pattern[0].size();
    const int positionsLength = textLength - patternLength + 1;
    const int radix = 31;

    // vector that stores powers of radix
    vector<long long> radixPowers(max (patternLength, textLength));
    radixPowers[0] = 1;
    for (int i = 1; i < radixPowers.size(); ++i)
    {
        radixPowers[i] = radixPowers[i - 1] * radix;
    }

    // matrix that stores values of hash function for the text
    vector<vector<long long> > hashFunction (textLength);
    for (int i = 0; i < textLength; ++i)
    {
        hashFunction[i].assign(textLength, 0);
        for (int j = 0; j < textLength; ++j)
        {
            hashFunction[i][j] = (text[i][j] - 'a' + 1) * radixPowers[j];
            if (j != 0)
            {
                hashFunction[i][j] += hashFunction[i][j - 1];
            }
            //cout << "hash function [" << i << "][" << j << "] = " << hashFunction[i][j] << endl;
        }
    }

    // keys - values of hash function to search in the text
    vector<long long> keys(patternLength);
    for (int i = 0; i < patternLength; ++i)
    {
        keys[i] = 0;
        for (int j = 0; j < patternLength; ++j)
        {
            keys[i] += (pattern[i][j] - 'a' + 1) * radixPowers[j];
        }
    }

    // i - number of row, j - keys[j] was found at position positionsOfPattern[i][j]
    vector <vector<int> > positionsOfPattern(textLength);

    // searching keys
    for (int i = 0; i < textLength; ++i)
    {
        positionsOfPattern[i].assign(patternLength, 0);
        for (int j = 0; j < positionsLength; ++j)
        {
            long long currentValue = hashFunction[i][j + patternLength - 1];
            if (j != 0)
            {
                currentValue -= hashFunction[i][j - 1];
            }

            for (int k = 0; k < min(int(i + 1), patternLength); ++k)
            {
                if (currentValue == keys[k] * radixPowers[j])
                {
                    positionsOfPattern[i][k] = j + 1; // saving found position
                }
            }
        }
    }

    for (int i = 0; i < textLength; ++i)
    {
        for (int k = 0; k < patternLength; ++k)
        {
            cout << "Position[" << i << "][" << k << "] = " << positionsOfPattern[i][k] << endl;
        }
    }

    //printing result
    bool matchFound = false;
    for (int i = 0; i < textLength; ++i)
    {
        for (int k = 0; k < patternLength; ++k)
        {
            if (positionsOfPattern[i][k] != 0)
            {
                bool printResult = true;
                int shift = positionsOfPattern[i][k];

                int l = k + 1;
                for (int j = i + 1; j < positionsLength + 1; ++j, ++l)
                {
                    if (positionsOfPattern[j][l] != shift) // for each row shift must be the same
                    {
                        printResult = false;
                        break;
                    }
                    if (printResult)
                    {
                        matchFound = true;
                        cout << "Pattern was found in the text. Position(row, column): ("
                            << i + 1 << ", " << positionsOfPattern[i][k] << ")" << endl;
                    }
                }
            }
        }
    }

    if (!matchFound)
    {
        cout << "No match!" << endl;
    }
}

void TestRabinKarp()
{
    string text = "Jim saw me in a barbershop.";
    string pattern = "barber";
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    RabinKarpSearch(text, pattern);
}

void TestRabinKarp2D()
{
    const int textSize = 3;
    const int patternSize = 2;
    string* text = new string[textSize];
    string* pattern = new string[patternSize];

    text[0] = "bcc";
    text[1] = "caa";
    text[2] = "abb";

    pattern[0] = "ca";
    pattern[1] = "ab";

    cout << "Text: " << endl;
    for (int i = 0; i < textSize; ++i)
    {
        cout << text[i] << endl;
    }

    cout << "Pattern: " << endl;
    for (int i = 0; i < patternSize; ++i)
    {
        cout << pattern[i] << endl;
    }
    RabinKarpSearch2D(text, pattern);
}

int main()
{
    //TestRabinKarp();
    TestRabinKarp2D();
}
