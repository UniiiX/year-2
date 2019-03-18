#include "catch.hpp"
#include "SplayTree.h"
#include "MyData.h"


TEST_CASE("Check if splay tree works fine with integers", "[SplayTree]")
{
    SplayTree<int, int> splayTree;
    SECTION("Check constructing empty splay tree")
    {
        REQUIRE(splayTree.getRoot() == nullptr);
    }


    SECTION("Examine insertion into splay tree")
    {
        splayTree.insert(3, 90);

        SECTION("Check empty splay tree case")
        {
            REQUIRE(splayTree.getRoot()->key == 3);
            REQUIRE(splayTree.getRoot()->value == 90);
            REQUIRE(splayTree.getRoot()->parent == nullptr);
            REQUIRE(splayTree.getRoot()->left == nullptr);
            REQUIRE(splayTree.getRoot()->right == nullptr);
        }

        splayTree.insert(3, 30);

        SECTION("Check that value in the node is replaced in the case of the same keys")
        {
            REQUIRE(splayTree.getRoot()->key == 3);
            REQUIRE(splayTree.getRoot()->value == 30);
            REQUIRE(splayTree.getRoot()->parent == nullptr);
            REQUIRE(splayTree.getRoot()->left == nullptr);
            REQUIRE(splayTree.getRoot()->right == nullptr);
        }

        splayTree.insert(1, 30);

        SECTION("Check if inserted element becomes new root")
        {
            REQUIRE(splayTree.getRoot()->key == 1);
            REQUIRE(splayTree.getRoot()->value == 30);
        }

        SECTION("Check that values can be duplicated")
        {
            REQUIRE(splayTree.getRoot()->right->value == splayTree.getRoot()->value);
        }

        splayTree.insert(2, 20);
        splayTree.insert(6, 60);
        splayTree.insert(5, 50);
        splayTree.insert(4, 40);


        SECTION("Check final state of the tree")
        {
            SECTION("Check root")
            {
                REQUIRE(splayTree.getRoot()->parent == nullptr);
                REQUIRE(splayTree.getRoot()->key == 4);
                REQUIRE(splayTree.getRoot()->value == 40);
            }

            SECTION("Check right subtree")
            {
                REQUIRE(splayTree.getRoot()->right->parent == splayTree.getRoot());
                REQUIRE(splayTree.getRoot()->right->key == 5);
                REQUIRE(splayTree.getRoot()->right->value == 50);

                REQUIRE(splayTree.getRoot()->right->right->parent == splayTree.getRoot()->right);
                REQUIRE(splayTree.getRoot()->right->right->key == 6);
                REQUIRE(splayTree.getRoot()->right->right->value == 60);
            }

            SECTION("Check left subtree")
            {
                REQUIRE(splayTree.getRoot()->left->parent == splayTree.getRoot());
                REQUIRE(splayTree.getRoot()->left->key == 2);
                REQUIRE(splayTree.getRoot()->left->value == 20);

                REQUIRE(splayTree.getRoot()->left->left->parent == splayTree.getRoot()->left);
                REQUIRE(splayTree.getRoot()->left->left->key == 1);
                REQUIRE(splayTree.getRoot()->left->left->value == 30);

                REQUIRE(splayTree.getRoot()->left->right->parent == splayTree.getRoot()->left);
                REQUIRE(splayTree.getRoot()->left->right->key == 3);
                REQUIRE(splayTree.getRoot()->left->right->value == 30);
            }
        }
    }


    splayTree.insert(3, 30);
    splayTree.insert(1, 30);
    splayTree.insert(2, 20);
    splayTree.insert(6, 60);
    splayTree.insert(5, 50);
    splayTree.insert(4, 40);

    int rootKey = splayTree.getRoot()->key;
    int rootValue = splayTree.getRoot()->value;
    int leafKey = splayTree.getRoot()->right->right->key;
    int leafValue = splayTree.getRoot()->right->right->value;
    int innerNodeKey = splayTree.getRoot()->right->key;
    int innerNodeValue = splayTree.getRoot()->right->value;
    int absentKey = 0;

    // checking that the node is actually leaf
    REQUIRE(splayTree.getRoot()->right->right->parent != nullptr);
    REQUIRE(splayTree.getRoot()->right->right->right == nullptr);
    REQUIRE(splayTree.getRoot()->right->right->left == nullptr);

    // checking that the node is actually inner
    REQUIRE(splayTree.getRoot()->right->parent != nullptr);
    // this boolean variable is needed, because
    // REQUIRE does not support operator "||"
    bool isInner = (splayTree.getRoot()->right->right != nullptr ||
                    splayTree.getRoot()->right->left != nullptr);
    REQUIRE(isInner);


    SECTION("Examine searching in splay tree")
    {
        SECTION("Searching for the root")
        {
            REQUIRE(splayTree.search(rootKey)->key == rootKey);
            REQUIRE(splayTree.search(rootKey)->value == rootValue);
            SECTION("Check that root remains the same after searching for it")
            {
                REQUIRE(splayTree.getRoot()->key == rootKey);
                REQUIRE(splayTree.getRoot()->value == rootValue);
            }
        }

        SECTION("Searching for leaf")
        {
            REQUIRE(splayTree.search(leafKey)->key == leafKey);
            REQUIRE(splayTree.search(leafKey)->value == leafValue);
            SECTION("Check that leaf that was found becomes the new root")
            {
                REQUIRE(splayTree.getRoot()->key == leafKey);
                REQUIRE(splayTree.getRoot()->value == leafValue);
            }
        }

        SECTION("Searching for inner node")
        {
            REQUIRE(splayTree.search(innerNodeKey)->key == innerNodeKey);
            REQUIRE(splayTree.search(innerNodeKey)->value == innerNodeValue);
            SECTION("Check that inner node that was found becomes the new root")
            {
                REQUIRE(splayTree.getRoot()->key == innerNodeKey);
                REQUIRE(splayTree.getRoot()->value == innerNodeValue);
            }
        }

        SECTION("Searching for absent key")
        {
            REQUIRE(splayTree.search(absentKey) == nullptr);
            SECTION("Check that root remains the same after searching for absent key")
            {
                REQUIRE(splayTree.getRoot()->key == rootKey);
                REQUIRE(splayTree.getRoot()->value == rootValue);
            }
        }
    }


    SECTION("Examine removing from the splay tree")
    {
        SECTION("Removing the root")
        {
            splayTree.remove(rootKey);
            SECTION("Check that the key has been removed from the tree")
            {
                REQUIRE(splayTree.search(rootKey) == nullptr);
            }
        }

        SECTION("Removing leaf")
        {
            splayTree.remove(leafKey);
            SECTION("Check that the key has been removed from the tree")
            {
                REQUIRE(splayTree.search(leafKey) == nullptr);
            }
        }

        SECTION("Removing inner node")
        {
            splayTree.remove(innerNodeKey);
            SECTION("Check that the key has been removed from the tree")
            {
                REQUIRE(splayTree.search(innerNodeKey) == nullptr);
            }
        }

        SECTION("Removing absent key")
        {
            // checking that the key is actually absent
            REQUIRE(splayTree.search(absentKey) == nullptr);

            splayTree.remove(absentKey);
            SECTION("Check that the root has remained the same")
            {
                REQUIRE(splayTree.getRoot()->key == rootKey);
                REQUIRE(splayTree.getRoot()->value == rootValue);
            }
        }
    }
}
