#define CATCH_CONFIG_RUNNER

#include <cstdlib>
#include <vector>

#include "SplayTree.h"
#include "MyData.h"
#include "catch.hpp"

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

void testBinarySearchTree()
{
    BinarySearchTree<int, int> bst;
    bst.insert(12, 15);
    bst.insert(11, 15);
    bst.insert(13, 15);
    bst.insert(14, 15);
    bst.insert(15, 15);
    bst.insert(1, 15);
    bst.print();
    cout << " =========================== " << endl;
    bst.remove(12);
    bst.remove(13);
    bst.print();
}

void printExampleForCatch2UnitTest()
{
    SplayTree<int, int> splayTree;
    splayTree.insert(3, 10);
    splayTree.insert(1, 20);
    splayTree.insert(2, 10);
    splayTree.insert(6, 20);
    splayTree.insert(5, 10);
    splayTree.insert(4, 20);
    splayTree.print();
}

int main(int argc, char* argv[])
{
    //testInt();
    //testMyData();
    //testBinarySearchTree();
    //printExampleForCatch2UnitTest();
    return Catch::Session().run(argc, argv);
}
