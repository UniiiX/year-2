#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


struct Element
{
    int data;
    int key;
    Element()
    {
        data = rand() % 100;
        key = rand() % 2;
    }
};

void PrintArray(Element* arrayToPrint, int size)
{
    cout << "Printing data: " << endl;
    for (int i(0); i < size; i++)
    {
        cout << arrayToPrint[i].data << " ";
    }
    cout << endl << "Printing keys: " << endl;
    for (int i(0); i < size; i++)
    {
        cout << arrayToPrint[i].key << "  ";
    }
    cout << endl;
}

// stable, O(n^2), constant auxiliary memory
void InsertionSort(Element* array, int size)
{
    for (int i(0); i < size; i++)
    {
        int j = i;
        while (j > 0 && array[j].key < array[j - 1].key)
        {
            swap(array[j], array[j - 1]);
            j--;
        }
    }
}

// stable, O(n), auxiliary memory used is proportional to the size of the array
Element* MySort1(Element* array, int size)
{
    Element* result = new Element[size];
    int left = 0;
    int right = 0;
    for (int i(0); i < size; i++)
    {
        if (array[i].key == 0)
        {
            right++;
        }
    }
    for (int i(0); i < size; i++)
    {
        if (array[i].key == 0)
        {
            result[left] = array[i];
            left++;
        }
        else
        {
            result[right] = array[i];
            right++;
        }
    }
    return result;
}

// unstable, O(n), constant auxiliary memory
void MySort2(Element* array, int size)
{
    int currentZeroKey = size - 1;
    int currentOneKey = 0;
    while (currentOneKey < currentZeroKey)
    {
        while (array[currentZeroKey].key != 0)
        {
            currentZeroKey--;
            if (currentZeroKey < 0)
            {
                return;
            }
        }
        while (array[currentOneKey].key != 1)
        {
            currentOneKey++;
            if (currentOneKey >= size)
            {
                return;
            }
        }
        if (currentZeroKey > currentOneKey)
        {
            swap(array[currentOneKey], array[currentZeroKey]);
            currentOneKey++;
            currentZeroKey--;
        }
    }
}

int main()
{
    srand(time(NULL));
    const int size = 15;
    Element* array = new Element[size];
    PrintArray(array, size);
    InsertionSort(array, size);
    PrintArray(array, size);
    delete[] array;

    cout << endl << endl;

    array = new Element[size];
    PrintArray(array, size);
    Element* sortedArray = MySort1(array, size);
    PrintArray(sortedArray, size);
    delete[] array;
    delete[] sortedArray;

    cout << endl << endl;

    array = new Element[size];
    PrintArray(array, size);
    MySort2(array, size);
    PrintArray(array, size);
    delete[] array;
}
