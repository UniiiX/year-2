#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <ctime>


using namespace std;

/* #################################################################### */

int Horspool(string T,string P)
{
    int n = T.length();

    int m = P.length();

    int Slide[255];
    for(int i=0; i<255; i++)
    {
        Slide[i]=m;
    }
    for(int l=0; l<m-1; l++)
    {
        Slide[P[l]] = m -1- l;

    }
    int i=m-1;

    while(i <= (n - 1))
    {
        int k=0;
        while(k<= m-1 && P[m-1-k]==T[i-k])
        {
            k=k+1;
        }

        if (k==m)
            return i-m+2;

        else
        {
            i= i+ Slide[T[i]];
        }
    }

    return -1;
}

/* #################################################################### */

int max(int a, int b)
{
    return (a > b) ? a : b;
}


void badCharHeuristic( string str, int size, int badchar[256])
{
    int i;

    for (i = 0; i < 256; i++) badchar[i] = -1;

    for (i = 0; i < size; i++) badchar[(int) str[i]] = i;
}

int Boyer_Moore(string T, string P)
{
    //bool tmp = false;
    int m = P.length();
    int n = T.length();

    int badchar[256];

    badCharHeuristic(P, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && P[j] == T[s + j])
            j--;

        if (j < 0)
        {
            return s+1;
            //s += (s + m < n) ? m - badchar[T[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badchar[T[s + j]]);
        }
    }

    return -1;
}

/* #################################################################### */

int Rabin_Karp (string t, string s)
{
    const int p = 31;
    vector<long long> p_pow (max (s.length(), t.length()));
    p_pow[0] = 1;
    for (size_t i=1; i<p_pow.size(); ++i)
    {
        p_pow[i] = p_pow[i-1] * p;
    }

    vector<long long> h (t.length());
    for (size_t i=0; i<t.length(); ++i)
    {
        h[i] = (t[i] - 'a' + 1) * p_pow[i];
        if (i)  h[i] += h[i-1];
    }

    long long h_s = 0;
    for (size_t i=0; i<s.length(); ++i)
    {
        h_s += (s[i] - 'a' + 1) * p_pow[i];
    }

    for (size_t i = 0; i + s.length() - 1 < t.length(); ++i)
    {
        long long cur_h = h[i+s.length()-1];
        if (i)
        {
            cur_h -= h[i-1];
        }

        if (cur_h == h_s * p_pow[i])
        {
           // cout << " Search result found, from position " << i+1 << endl;
            return i+1;
        }
    }

    return -1;

}

/* #################################################################### */

void computeLPSArray(string pat, int M, int* lps)
{
    int len = 0;

    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMP(string T, string P)
{
    int M = P.length();
    int N = T.length();

    int lps[M];

    computeLPSArray(T, M, lps);

    int i = 0;
    int j = 0;
    while (i < N)
    {
        if (P[j] == T[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            j = lps[j - 1];
            return i - j ;

        }

        else if (i < N && P[j] != T[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }

    return -1;
}

/* #################################################################### */

int simple ( string T , string P)
{
    int res = 0;
    bool tmp = true;
    int I;
int J;
    for (int i = 0; i < P.size(); i++)
    {
        for (int j = 0; j < T.size(); j++)
        {
            if (T[j] == P[i])
            {
                I = i;
                J = j;
                while (I <= P.size() && J <= T.size())
                {
                    if (T[J] == P[I])
                    {
                        J++;
                        I++;
                    }
                    else
                    {
                        tmp = false;
                    }
                }

                if (tmp)
                {
                    return res+1;
                }
                else
                {
                    return -1;
                }

            }
            res++;
        }
    }
    return -1;
}

/* #################################################################### */

void timeOfFunc (string T, string P)
{
    unsigned int start_time =  clock();
    Horspool(T, P);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << " Time of work of Horspool is " << search_time << " milliseconds " << endl;

    start_time =  clock();
    Boyer_Moore(T, P);
    end_time = clock();
    search_time = end_time - start_time;
    cout << " Time of work of Boyer_Moore is " << search_time << " milliseconds " << endl;

    start_time =  clock();
    Rabin_Karp(T, P);
    end_time = clock();
    search_time = end_time - start_time;
    cout << " Time of work of Boyer_Moore is " << search_time << " milliseconds " << endl;

    start_time =  clock();
    KMP(T, P);
    end_time = clock();
    search_time = end_time - start_time;
    cout << " Time of work of KMP is " << search_time << " milliseconds " << endl;

    start_time =  clock();
    simple(T, P);
    end_time = clock();
    search_time = end_time - start_time;
    cout << " Time of work of simple algorithm is " << search_time << " milliseconds \n" << endl;
}

/* #################################################################### */

bool Continue()
{
    cout<<endl;
    cout << " Back to menu (y(YES)/n(NO))?";
    char tmp;
    cin >> tmp;
    if (tmp == 'n')
    {
        //system("pause");
        return false;
    }
    else
    {
        //system("pause");
        return true;
    }
}

/* #################################################################### */

void writeRes(int pos )
{
    if( pos == -1)
    {
        cout << " The search has not given any results " << endl;
    }
    else
    {
        cout << " Search result found, from position " << pos << endl;
    }
}


/* #################################################################### */

void MenuFunction (string T, string P)
{
    bool tmp = true;
    int number;
    int pos;

    do {

        cout << " 1 - Horspool, 2 - Boyer_Moore, 3 - Rabin_Karp, 4 - KMP, 5 - simple, 6 - time of work \n";
        cout << "\n Put number: ";
        cin >> number;
        cout<<endl;


        switch (number)
        {
        case 1:
                pos = Horspool(T, P);
                writeRes(pos);

                tmp = Continue();
                break;

        case 2:
                pos = Boyer_Moore(T, P);
                writeRes(pos);

                tmp = Continue();
                break;

        case 3:
                pos = Rabin_Karp(T, P);
                writeRes(pos);

            tmp = Continue();
            break;
        case 4:
                pos = KMP(T, P);
                writeRes(pos);

                tmp = Continue();
                break;

        case 6:
                cout<< "\n -------- Time of work of our funcrions -------- " <<endl;
                timeOfFunc(T, P);

                tmp = Continue();
                break;

        case 5:
                pos = simple( T,P);
                writeRes(pos);

                tmp = Continue();
                break;
}
        cout << "\n ---------------------------------------------------------------- \n" <<endl;
    } while ( tmp );
}

/* #################################################################### */

int main()
{
    string T;
    string P;

    cin >> T;
    cin >> P;

    MenuFunction(T,P);
}
