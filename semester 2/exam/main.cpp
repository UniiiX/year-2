#include <iostream>
#include <cstdlib>

#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include "OrderedList.h"
#include "SimpleMap.h"
#include "MapLinkedListImpl.h"
#include "MapRedBlackTreeImpl.h"
#include "Set.h"
#include "SetLinkedListImpl.h"
#include "SetRedBlackTreeImpl.h"

using namespace std;
using namespace slc;
using namespace bst;
using namespace advalg;

void testList()
{
    auto cmp = std::greater<int>();
    OrderedList<int> ol(cmp);
    ol.append(1).append(2).append(33).append(55).insert(12, 0);
    cout << ol << endl;
    ol.remove(0);
    cout << ol << endl;

//    const int size = 10000;
//    int keys[size];
//    bool operations[size];
//    for (int i = 0; i < size; ++i)
//    {
//        operations[i] = rand() % 2;
//    }
//    for (int i = 0; i < size; ++i)
//    {
//        keys[i] = rand();
//        (operations[i]) ? ol.append(keys[i]) : ol.insert(keys[i], rand() % i);
//    }
//    cout << ol.getSize() << endl;
//    for (int i = size - 1; i >= 0; --i)
//    {
//        try
//        {
//            ol.remove(i);
//        }
//        catch (const InvalidIndex &)
//        {
//
//        }
//    }
//    cout << ol.getSize() << endl;
}

void testBST()
{
    BinarySearchTree<int> bst(new PrintCommandLineColorlessStrategy<int>, std::greater<int>());
    bst.insert(4).insert(12).insert(3).insert(56).insert(1).insert(44).insert(122).insert(3231).insert(536).insert(11).print();
    bst.remove(4).remove(3).remove(12).remove(1).remove(56).print();
    if (bst.search(122))
    {
        cout << "found!" << endl;
    }
    cout << bst.minimum(bst.getRoot())->getKey() << endl;
}

void testRBT()
{
    RedBlackTree<int> rbt;
    rbt.insert(4).insert(12).insert(3).insert(56).insert(1).print();
    rbt.remove(4).remove(3).remove(12).remove(1).remove(56).print();
}

void testMap()
{
    // circular linked list based implementation
    SimpleMap<int, int> llm(new MapLinkedListImpl<int, int>);
    llm.insert(1, 10).insert(13, 130).insert(41, 410);
    cout << llm.getKeys() << endl;
    cout << llm.getValues() << endl;
    llm.remove(13);
    cout << llm.getKeys() << endl;
    cout << llm.getValues() << endl;


    // red-black tree based implementation
    SimpleMap<int, int> rbtm(new MapRedBlackTreeImpl<int, int>);
    rbtm.insert(1, 10).insert(13, 130).insert(41, 410);
    cout << "Printing keys: " << rbtm.getKeys() << endl;
    cout << "Printing values: " << rbtm.getValues() << endl;
    rbtm.remove(13);
    cout << "Removing key 13" << endl;
    cout << "Printing keys once again: " << rbtm.getKeys() << endl;
    cout << "Printing values once again: " << rbtm.getValues() << endl;
    cout << "Printing value at key 41: " << *rbtm[41] << endl;
}

void testSet()
{
    Set<int> sll(new SetLinkedListImpl<int>);
    sll.insert(1).insert(2).insert(3).insert(5).insert(8).insert(9).insert(10);
    cout << sll.belongs(1) << " " << sll.belongs(4) << endl;
    sll.remove(1);
    cout << sll.belongs(1) << endl;

    Set<int> srbt(new SetRedBlackTreeImpl<int>);
    srbt.insert(1).insert(2).insert(3).insert(5).insert(8).insert(9).insert(10);
    cout << srbt.belongs(1) << " " << srbt.belongs(4) << endl;
    srbt.remove(1);
    cout << srbt.belongs(1) << endl;
}

int main()
{
//    testList();
//    testBST();
//    testRBT();
//    testMap();
//    testSet();
}
