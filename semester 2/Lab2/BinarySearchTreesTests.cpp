#include "BinarySearchTreesInvariants.h"
#include "BinarySearchTreesFacade.h"

#include <cstdlib>
#include <vector>
#include <catch.hpp>

using namespace bst;

typedef BinarySearchTreesInvariants<int, int> Check;

void checkProperInvariant(BinarySearchTree<int, int> & target)
{
    auto type = target.getType();
    switch (type)
    {
    case TreeType::binarySearchTree:
    {
        REQUIRE(Check::obeysBinarySearchTreeInvariant(target));
        break;
    }
    case TreeType::redBlackTree:
    {
        REQUIRE(Check::obeysRedBlackTreeInvariant(target));
        break;
    }
    case TreeType::splayTree:
    {
        REQUIRE(Check::obeysBinarySearchTreeInvariant(target));
        break;
    }
    }
}

void binarySearchTreePreservesItsInvariants(
    const TreeType & type,
    const unsigned treesCount = 1e2,
    const unsigned nodesCountRange = 1e2,
    const int keysRangeLowerBound = -1e5,
    const int keysRangeUpperBound = 1e5)
{
    auto & facade = BinarySearchTreesFacade<int, int>::getInstance();
    auto target = facade.create(type);
    for (unsigned i = 0; i < treesCount; ++i)
    {
        const unsigned nodesCount = rand() % nodesCountRange;
        std::vector<int> keys(nodesCount);

        for (unsigned j = 0; j < nodesCount; ++j)
        {
            int key = keysRangeLowerBound + rand() % (keysRangeUpperBound - keysRangeLowerBound);
            keys.at(j) = key;
            target.insert(key, 0);
            checkProperInvariant(target);
        }

        for (unsigned j = 0; j < nodesCount; ++j)
        {
            const int keyIndex = rand() % keys.size();
            int key = keys.at(keyIndex);
            target.search(key);
            checkProperInvariant(target);
            // generated keys might repeat, hence key
            // might already be removed from the tree
            try
            {
                target.remove(key);
            }
            catch (const AbsentKey &)
            {
                // ignoring the possibility of key being absent
            }
            checkProperInvariant(target);
            keys.erase(keys.begin() + keyIndex);
        }
    }
}

TEST_CASE("Binary search tree preserves its invariant")
{
    binarySearchTreePreservesItsInvariants(TreeType::binarySearchTree);
}

TEST_CASE("Red-black tree preserves its invariant")
{
    binarySearchTreePreservesItsInvariants(TreeType::redBlackTree);
}

TEST_CASE("Splay tree preserves its invariant")
{
    binarySearchTreePreservesItsInvariants(TreeType::splayTree);
}
