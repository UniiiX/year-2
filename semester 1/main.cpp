#include <iostream>
#include <cstdlib>
#include <vector>

#define MaxValue 101

using namespace std;

void GenerateRandomVector(vector<int> &vec, int n)
{
    for(int i = 0; i < n; i++)
    {
        vec.push_back(rand() % (MaxValue - 1) + 1);
    }
}

void PrintVector(vector<int> &vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

vector<int> Merge(vector <int> a, vector <int> b)
{
    vector<int> result(a.size() + b.size());
    int index1 = 0;
    int index2 = 0;

    a.push_back(MaxValue);
    b.push_back(MaxValue);

    for(int i = 0; i < result.size(); i++)
    {
        if(a[index1] <= b[index2])
        {
            result[i] = a[index1];
            index1++;
        }
        else
        {
            result[i] = b[index2];
            index2++;
        }
    }
    return result;
}

vector<int> MergeSort(vector <int> vec)
{
    if (vec.size() == 1)
    {
        return vec;
    }
    vector<int> left, right;
    left.assign(vec.begin(), vec.end() - (vec.size() / 2));
    right.assign(vec.end() - (vec.size() / 2), vec.end());
    return Merge(MergeSort(left), MergeSort(right));
}

int main()
{
    vector<int> vec;
    int n;
    cout << "Input number of elements in the array: ";
    cin >> n;

    GenerateRandomVector(vec, n);
    cout << "Randomly generated array is: " << endl;
    PrintVector(vec);
    vec = MergeSort(vec);

    cout << "Sorted array: " << endl;
    PrintVector(vec);
}
