#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <cstdlib>
#include <vector>

#include <catch.hpp>
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

    if (bst.search(keys.at(size / 2)))
    {
        cout << "Found key " << keys.at(size / 2) << endl;
    }

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
    facade.print(rbTree);

    if (facade.search(rbTree, keys.at(size / 2)))
    {
        cout << "Found key " << keys.at(size / 2) << endl;
    }

    auto splayTree = facade.create(TreeType::splayTree);
    for (int i = 0; i < size; ++i)
    {
        facade.insert(splayTree, keys.at(i), 0);
    }
    facade.print(splayTree);
}

int main(int argc, char* argv[])
{
//    testBST();
//    testRBTree();
//    testSplayTree();
//    testFacade();
    return Catch::Session().run(argc, argv);
}
