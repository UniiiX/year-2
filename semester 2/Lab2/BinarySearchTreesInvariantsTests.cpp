#include "BinarySearchTreesInvariants.h"
#include <catch.hpp>

using namespace bst;

typedef BinarySearchTreesInvariants<int, int> Test;

TEST_CASE("obeysBinarySearchTreeInvariant() works correctly")
{
    auto leftLeft = Node<int, int>::createColorless(19, 117);
    auto rightLeft = Node<int, int>::createColorless(66, 123);
    auto rightRight = Node<int, int>::createColorless(100, 342);
    auto left = Node<int, int>::createColorless(25, 1093, nullptr, leftLeft);
    auto right = Node<int, int>::createColorless(75, 112, nullptr, rightLeft, rightRight);
    auto root = Node<int, int>::createColorless(50, 0, nullptr, left, right);
    left->setParent(root);
    right->setParent(root);
    leftLeft->setParent(left);
    rightLeft->setParent(right);
    rightRight->setParent(right);

    SECTION("Returns true on valid binary search trees")
    {
        // check that nodes build valid binary search tree
        REQUIRE(root->getKey() < root->getRight()->getKey());
        REQUIRE(root->getKey() > root->getLeft()->getKey());
        REQUIRE(root->getLeft()->getKey() > root->getLeft()->getLeft()->getKey());
        REQUIRE(root->getRight()->getKey() > root->getRight()->getLeft()->getKey());
        REQUIRE(root->getRight()->getKey() < root->getRight()->getRight()->getKey());
        REQUIRE(!root->getRight()->getRight()->getRight());
        REQUIRE(!root->getRight()->getRight()->getLeft());
        REQUIRE(!root->getRight()->getLeft()->getRight());
        REQUIRE(!root->getRight()->getLeft()->getLeft());
        REQUIRE(!root->getLeft()->getLeft()->getLeft());
        REQUIRE(!root->getLeft()->getLeft()->getRight());
        REQUIRE(!root->getLeft()->getRight());

        REQUIRE(Test::obeysBinarySearchTreeInvariant(root));
    }

    SECTION("Returns false on invalid binary search trees")
    {
        leftLeft->setKey(26);

        // check that binary search tree built from nodes is not valid
        REQUIRE(root->getLeft()->getKey() < root->getLeft()->getLeft()->getKey());

        REQUIRE(!Test::obeysBinarySearchTreeInvariant(root));
    }

    Node<int, int>::freeConnectedComponent(root);
}

TEST_CASE("rootIsBlack() works correctly")
{
    auto rbTree = RedBlackTreeFactory<int, int>().create();

    SECTION("Returns true if root is black")
    {
        SECTION("Returns true for null-node")
        {
            // check that root is actually nullptr
            REQUIRE(!rbTree.getRoot());

            REQUIRE(Test::rootIsBlack(rbTree));
        }
        SECTION("Returns true for black node")
        {
            rbTree.insert(0, 0);
            // check that root is actually black
            REQUIRE(rbTree.getRoot()->getColor() == Color::black);

            REQUIRE(Test::rootIsBlack(rbTree));
        }
    }

    SECTION("Returns false if root is red")
    {
        rbTree.insert(0, 0);
        Test::setRootColor(rbTree, Color::red);
        // check that root is actually red
        REQUIRE(rbTree.getRoot()->getColor() == Color::red);

        REQUIRE(!Test::rootIsBlack(rbTree));
    }
}

TEST_CASE("redNodeCantHaveRedChild() works correctly")
{
    auto left = Node<int, int>::createBlack(50, 2357);
    auto right = Node<int, int>::createBlack(150, 38);
    auto parent = Node<int, int>::createRed(100, 5217, nullptr, left, right);
    left->setParent(parent);
    right->setParent(parent);

    // check that parent is actually red
    REQUIRE(parent->getColor() == Color::red);

    SECTION("Returns true if both children are black")
    {
        SECTION("Returns true if both children are black nodes")
        {
            // check that both children are actually black nodes
            REQUIRE(parent->getLeft()->getColor() == Color::black);
            REQUIRE(parent->getRight()->getColor() == Color::black);

            REQUIRE(Test::redNodeCantHaveRedChild(parent));
        }

        SECTION("Returns true if left child is null and right is black")
        {
            parent->setLeft(nullptr);

            // check that left child is null and right is black
            REQUIRE(!parent->getLeft());
            REQUIRE(parent->getRight()->getColor() == Color::black);

            REQUIRE(Test::redNodeCantHaveRedChild(parent));
        }

        SECTION("Returns true if right child is null and left is black")
        {
            parent->setLeft(left);
            parent->setRight(nullptr);

            // check that left child is black and right is null
            REQUIRE(parent->getLeft()->getColor() == Color::black);
            REQUIRE(!parent->getRight());

            REQUIRE(Test::redNodeCantHaveRedChild(parent));
        }

        SECTION("Returns true if both children are null-nodes")
        {
            parent->setLeft(nullptr);
            parent->setRight(nullptr);

            // check that both children are null-nodes
            REQUIRE(!parent->getLeft());
            REQUIRE(!parent->getRight());

            REQUIRE(Test::redNodeCantHaveRedChild(parent));
        }
    }


    SECTION("Returns false if at least one child is red")
    {
        SECTION("Returns false if left child is red")
        {
            left->setColor(Color::red);
            parent->setLeft(left);
            parent->setRight(nullptr);

            SECTION("Returns false if left child is red and right is null")
            {
                // check that left child is red and right is null
                REQUIRE(parent->getLeft()->getColor() == Color::red);
                REQUIRE(!parent->getRight());

                REQUIRE(!Test::redNodeCantHaveRedChild(parent));
            }
            SECTION("Returns false if left child is red and right is black")
            {
                parent->setRight(right);

                // check that left child is red and right is black
                REQUIRE(parent->getLeft()->getColor() == Color::red);
                REQUIRE(parent->getRight()->getColor() == Color::black);

                REQUIRE(!Test::redNodeCantHaveRedChild(parent));
            }
        }

        SECTION("Returns false if right child is red")
        {
            left->setColor(Color::black);
            right->setColor(Color::red);
            parent->setRight(right);

            SECTION("Returns false if right child is red and left is black")
            {
                // check that right child is red and left is black
                REQUIRE(parent->getRight()->getColor() == Color::red);
                REQUIRE(parent->getLeft()->getColor() == Color::black);

                REQUIRE(!Test::redNodeCantHaveRedChild(parent));
            }

            SECTION("Returns false if right child is red and left is null")
            {
                parent->setLeft(nullptr);

                // check that right child is red and left is null
                REQUIRE(parent->getRight()->getColor() == Color::red);
                REQUIRE(!parent->getLeft());

                REQUIRE(!Test::redNodeCantHaveRedChild(parent));
            }
        }

        SECTION("Returns false if both children are red")
        {
            left->setColor(Color::red);
            right->setColor(Color::red);

            // check that both children are red
            REQUIRE(parent->getLeft()->getColor() == Color::red);
            REQUIRE(parent->getRight()->getColor() == Color::red);

            REQUIRE(!Test::redNodeCantHaveRedChild(parent));
        }

    }

    Node<int, int>::freeConnectedComponent(parent);
}


TEST_CASE("nodesAreEitherBlackOrRed() works correctly")
{
    auto target = Node<int, int>::createRed(1324, 43229);
    SECTION("Returns true on red node")
    {
        // check that node is actually red
        REQUIRE(target->getColor() == Color::red);

        REQUIRE(Test::nodesAreEitherBlackOrRed(target));
    }
    SECTION("Returns true on black node")
    {
        target->setColor(Color::black);
        // check that node is actually black
        REQUIRE(target->getColor() == Color::black);

        REQUIRE(Test::nodesAreEitherBlackOrRed(target));
    }
    SECTION("Returns true on null-node")
    {
        REQUIRE(Test::nodesAreEitherBlackOrRed(nullptr));
    }
    SECTION("Returns false on colorless node")
    {
        target->setColor(Color::none);
        // check that node is actually colorless
        REQUIRE(target->getColor() == Color::none);

        REQUIRE(!Test::nodesAreEitherBlackOrRed(target));
    }
    delete target;
}

TEST_CASE("calculateLeftBranchBlackHeight() works correctly")
{
    auto root = Node<int, int>::createBlack(65, 0);
    auto left = Node<int, int>::createRed(50, 0, root);
    auto leftLeft = Node<int, int>::createBlack(45, 0, left);
    auto leftLeftLeft = Node<int, int>::createBlack(35, 0, leftLeft);
    root->setLeft(left);
    left->setLeft(leftLeft);
    leftLeft->setLeft(leftLeftLeft);

    // check that both root and left actually have left branch black height equal to 3
    REQUIRE(root->getLeft()->getColor() == Color::red);
    REQUIRE(root->getLeft()->getLeft()->getColor() == Color::black);
    REQUIRE(root->getLeft()->getLeft()->getLeft()->getColor() == Color::black);
    REQUIRE(!root->getLeft()->getLeft()->getLeft()->getLeft());

    SECTION("root has left branch black height equal to 3")
    {
        REQUIRE(Test::calculateLeftBranchBlackHeight(root) == 3);
    }

    SECTION("left has left branch black height equal to 2")
    {
        REQUIRE(Test::calculateLeftBranchBlackHeight(left) == 2);
    }

    SECTION("leftLeftLeft has left branch black height equal to 1")
    {
        REQUIRE(Test::calculateLeftBranchBlackHeight(leftLeftLeft) == 1);
    }

    SECTION("leaf has left branch black height equal to 0")
    {
        REQUIRE(Test::calculateLeftBranchBlackHeight(nullptr) == 0);
    }

    Node<int, int>::freeConnectedComponent(root);
}

TEST_CASE("simplePathsBlackLengthsAreEqual() works correctly")
{
    auto leftLeft = Node<int, int>::createRed(19, 117);
    auto rightLeft = Node<int, int>::createRed(66, 123);
    auto left = Node<int, int>::createBlack(25, 1093, nullptr, leftLeft);
    auto right = Node<int, int>::createBlack(75, 112, nullptr, rightLeft);
    auto root = Node<int, int>::createBlack(50, 0, nullptr, left, right);
    left->setParent(root);
    right->setParent(root);
    leftLeft->setParent(left);
    rightLeft->setParent(right);

    SECTION("Returns true on black paths of equal length")
    {
        // check that all simple paths have the same black length
        REQUIRE(root->getLeft()->getColor() == Color::black);
        REQUIRE(root->getRight()->getColor() == Color::black);
        REQUIRE(root->getLeft()->getLeft()->getColor() == Color::red);
        REQUIRE(!root->getLeft()->getRight());
        REQUIRE(root->getRight()->getLeft()->getColor() == Color::red);
        REQUIRE(!root->getRight()->getRight());

        SECTION("All simple paths from root have same black length")
        {
            REQUIRE(Test::simplePathsBlackLengthsAreEqual(root));
        }

        SECTION("All simple paths from left have same black length")
        {
            REQUIRE(Test::simplePathsBlackLengthsAreEqual(root->getLeft()));
        }

        SECTION("All simple paths from right have same black length")
        {
            REQUIRE(Test::simplePathsBlackLengthsAreEqual(root->getRight()));
        }

        SECTION("All simple paths from leftLeft same black length")
        {
            REQUIRE(Test::simplePathsBlackLengthsAreEqual(root->getLeft()->getLeft()));
        }

        SECTION("All simple paths from null-node have same black length")
        {
            REQUIRE(Test::simplePathsBlackLengthsAreEqual(nullptr));
        }
    }

    SECTION("Returns false on black paths of different length")
    {
        leftLeft->setColor(Color::black);

        // check that at least two simple paths from root
        // and from left have different black length
        REQUIRE(root->getLeft()->getLeft()->getColor() == Color::black);
        REQUIRE(!root->getLeft()->getRight());

        SECTION("Not all simple paths from root have same black length")
        {
            REQUIRE(!Test::simplePathsBlackLengthsAreEqual(root));
        }

        SECTION("Not all simple paths from left have same black length")
        {
            REQUIRE(!Test::simplePathsBlackLengthsAreEqual(root->getLeft()));
        }
    }

    Node<int, int>::freeConnectedComponent(root);
}
