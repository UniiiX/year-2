# This is bst(Binary Search Trees) library usage tutorial

* ## Tree types
Currently bst library supports three types of binary search trees, that is: [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree) itself, [splay tree](https://en.wikipedia.org/wiki/Splay_tree) and [red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)

* ## Namespace
Everything in bst library lives within a bst namespace.
You can access classes either by adding `using namespace bst` at the beginning of your file **or**
by prefixing every class with bst like this: `bst::BinarySearchTree<int, int> = bst::BinarySearchTreeFactory<int, int>().create();`
*Don't worry if you don't understand what the code above does, we will come back to explaining it later.*
From now on we will assume that code in the following examples has `using namespace bst` string somewhere before it for simplicity.

* ## Template parameters
**Every** single class (except for enum classes like TreeType and Color) in bst library is template with **two** paramemters:
  1. key
  2. value
This is due to tree nodes containing key and value inside them, so binary search trees from the library can be used as a map

* ## **Three** different levels of library usage
There are 3 different levels that you can use bst library at:
the more difficult the level is - the more powerful functionality it provides you with.
Let's go through them in the least difficulty order
### Using bst library through its facade:
If you all you need is the most basic functionality then there is no better way to use bst than through `BinarySearchTreeFacade` class
Lets's have a closer look at the tools it provides you with
#### Creating binary search trees: 
`BinarySearchTree<int, int> bst = BinarySearchTreeFacade<int, int>::getInstance().create(TreeType::binarySearchTree);` **or**
you can kind of ommit the boring part using auto: 
`auto bst =  BinarySearchTreeFacade<int, int>::getInstance().create(TreeType::binarySearchTree);`
Well... Doesn't look like we've managed to ommit the boring part, but that's crucial! 
Note that BinarySearchTreeFacade is a singleton class.
That's why when it comes down not to only creating a binary search tree using facade may become a really painful experience.
What I suggest is to save the facade instance into a variable and then 
use it instead of the ugly expression to the right of = operator:
    auto & facade = BinarySearchTreeFacade<int, int>::getInstance();
    auto bst = facade.create(TreeType::binarySearchTree);
    auto rbt = facade.create(TreeType::redBlackTree);
    auto st = facade.create(TreeType::splayTree);
Here enum class TreeType is used as an argument to specify what kind of binarySearchTree you want to create
    
#### Inserting elements: 
Suppose we've created our trees as in the example above and what we want to do now is to insert some elements into them
That's how you can do it with facade: `facade.insert(bst, 20, 100);` 
Here we inserted node with the key 20 and value 100 into the BinarySearchTree instance of type
TreeType::binarySearchTree we had created earlier on.
Same syntax facade.insert(tree, key, value) goes for other types of trees as well.
    
#### Removing elements:
Pretty much the same as inserting elements except for you don't need to pass the value into the method: 
`facade.remove(bst, 20);`
If you pass into remove method a key that is absent in the tree AbsentKey exception will be thrown, that's why
if you are not sure if a key is present in the tree or not better wrap call of remove in try-catch block:
    try
    {
        facade.remove(bst, 0)
    }
    catch (const AbsentKey & exception)
    {
        // handle the exception
    }
    
**insert/remove return values:**
Actually it is not void as someone could've suggested, instead these methods return tree instance that was passed
as an argument, so you can chain calls of insert/remove like this: `facade.insert(bst, 1, 100).insert(bst, 2, 200);`
    
#### Element lookup:
Syntax for lookup looks as follows: facade.search(key)
Method returns const Node<K, V>* (K - type of key, V - type of value), 
so you can check whether a key is present in the tree like follows:
    using std::cout;
    auto found = facade.search(1);
    if (found)
    {
        std::cout << "Present";
    }
    else
    {
        std::cout << "Absent";
    }
    
#### Printing the tree into console: 
Probably the easiest part about using facade is printing the tree.
Just pass your tree instance into the print method `facade.print(bst);` and vuala!
Trees are printed using out-order tree traversal, right child above, left child below the parent,
children are indented with 4 spaces.
    
