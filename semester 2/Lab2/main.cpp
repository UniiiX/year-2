#include <iostream>
#include <cstdlib>
#include <vector>

#include <PrinterProxy.h>
#include <BinarySearchTree.h>
#include <BinarySearchTreesFacade.h>

using namespace std;
using namespace bst;

void testBST()
{
    auto bst = BinarySearchTreeFactory<int, int>().create();
    const int size = 50;
    vector<int> keys;

    for (int i = 0; i < size; ++i)
    {
        keys.push_back(rand() % 100);
        bst.insert(keys.at(i), 0);
    }
    PrinterProxy<int, int>::print(bst);

    for (int i = 0; i < size; ++i)
    {
        try
        {
            bst.remove(keys.at(i));
        }
        catch (const AbsentKey &) {}
    }
    PrinterProxy<int, int>::print(bst);
}

void testRBTree()
{
    auto rbTree = RedBlackTreeFactory<int, int>().create();
    const int size = 60;
    vector<int> keys;

    for (int i = 0; i < size; ++i)
    {
        keys.push_back(rand() % 1000);
        rbTree.insert(keys.at(i), 0);
    }
    PrinterProxy<int, int>::print(rbTree);
}

void testSplayTree()
{
    auto splayTree = SplayTreeFactory<int, int>().create();
    const int size = 60;
    vector<int> keys;

    for (int i = 0; i < size; ++i)
    {
        keys.push_back(rand() % 1000);
        splayTree.insert(keys.at(i), 0);
    }
    PrinterProxy<int, int>::print(splayTree);
}

void testFacade()
{
    auto & facade = BinarySearchTreesFacade<int, int>::getInstance();
    auto rbTree = facade.create(TreeType::redBlackTree);
    const int size = 60;
    vector<int> keys;

    for (int i = 0; i < size; ++i)
    {
        keys.push_back(rand() % 1000);
        facade.insert(rbTree, keys.at(i), 0);
    }
    BinarySearchTreesFacade<int, int>::getInstance().print(rbTree);

    auto splayTree = facade.create(TreeType::splayTree);
    for (int i = 0; i < size; ++i)
    {
        facade.insert(splayTree, keys.at(i), 0);
    }
    facade.print(splayTree);
}

int main()
{
//    testBST();
//    testRBTree();
//    testSplayTree();
//    testFacade();
}
