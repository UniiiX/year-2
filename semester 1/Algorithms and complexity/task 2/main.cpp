#include <iostream>
#include <cstdlib>

using namespace std;

int& Get(int i, bool getBolt, int* bolts, int* nuts)
{
    return (getBolt ? bolts[i] : nuts[i]);
}

void QuickSort(int* bolts, int* nuts, bool sortBolts, int left, int right, int pivot = -1, int previousL = 0, int previousR = 0)
{
    int l = left;
    int r = right;
    if (pivot == -1)
    {
        pivot = Get((l + r) / 2, !sortBolts, bolts, nuts);
    }
    int nextPivot = -1;

    while (l < r)
    {
        while (Get(l, sortBolts, bolts, nuts) < pivot)
        {
            l++;
        }
        while (Get(r, sortBolts, bolts, nuts) > pivot)
        {
            r--;
        }
        if (Get(l, sortBolts, bolts, nuts) == pivot)
        {
            nextPivot = Get(l, sortBolts, bolts, nuts);
        }
        else if (Get(r, sortBolts, bolts, nuts) == pivot)
        {
            nextPivot = Get(r, sortBolts, bolts, nuts);
        }
        if (l <= r)
        {
            swap(Get(l, sortBolts, bolts, nuts), Get(r, sortBolts, bolts, nuts));
            l++;
            r--;
        }
    }

    if (sortBolts)
    {
        sortBolts = false;
        previousL = l;
        previousR = r;
        QuickSort(bolts, nuts, sortBolts, left, right, nextPivot, previousL, previousR);
    }
    else
    {
        sortBolts = true;
        l = min(l, previousL);
        r = max(r, previousR);
        if (left < r) QuickSort(bolts, nuts, sortBolts, left, r);
        if (l < right) QuickSort(bolts, nuts, sortBolts, l, right);
    }
}

void InputArray(int* arrayToInput, int size)
{
    for (int i = 0; i < size; i++)
    {
        cin >> arrayToInput[i];
    }
}

void PrintPairs(int* bolts, int* nuts, int size)
{
    cout << "Pairs of nuts and bolts: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << bolts[i] << " " << nuts[i] << endl;
    }
}

int main()
{
    int size;
    cout << "Input number of bolts and nuts: ";
    cin >> size;
    int* bolts = new int[size];
    int* nuts = new int[size];

    cout << "Input sizes of bolts: " << endl;
    InputArray(bolts, size);

    cout << "Input sizes of nuts: " << endl;
    InputArray(nuts, size);

    QuickSort(bolts, nuts, true, 0, size - 1);

    PrintPairs(bolts, nuts, size);
    delete[] bolts;
    delete[] nuts;
}
