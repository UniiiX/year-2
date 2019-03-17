#include <iostream>
#include <cstdlib>
#include <vector>

#include <SplayTree.h>
#include <MyData.h>

using namespace std;

void testInt()
{
    SplayTree<int, int> splayTree;
    const int size = 30;
    int keys[size];
    int values[size];
    for (int i(0); i < size; i++)
    {
        keys[i] = rand() % 100;
        values[i] = rand() % 100;
        splayTree.insert(keys[i], values[i]);
        //splayTree.print();
        //cout << "==================================================================" << endl;
    }

    splayTree.print();

    for (int i(0); i < size; i++)
    {
        //cout << "==================================================================" << endl;
        //cout << "Removing " << keys[i] << endl;
        splayTree.remove(keys[i]);
        //splayTree.print();
    }
}

void testMyData()
{
    setlocale(LC_ALL, "rus");
    Group group("group.txt");
    SplayTree<double, string> splayTree;
    vector<double> keys;
    for (auto student : group.getStudents())
    {
        keys.push_back(rand() % 100);
        student->setGradePointAverage(keys.at(keys.size() - 1));
        splayTree.insert(student->getGradePointAverage(), student->getLastName());
//        splayTree.print();
//        cout << "==================================================================" << endl;
    }

    group.print();

    const double key = 18;
    if (splayTree.search(key))
    {
        cout << splayTree.search(key)->value << endl;
    }

    splayTree.print();
//    for (int i(0); i < group.getSize(); i++)
//    {
//        //cout << "==================================================================" << endl;
//        //cout << "Removing " << keys[i] << endl;
//        splayTree.remove(keys[i]);
//        //splayTree.print();
//    }
}

int main()
{
    //testInt();
    testMyData();
}
