// 207723198
// yair852258@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "Tree.hpp"

using namespace std;

TEST_CASE("Comlex nodes Compare")
{
    Complex c1(3.5, 2.0);
    Complex c2(1.5, 1.0);
    Complex c3(5.3, 11.0);
    Complex c4(7.2, 2.1);
    Complex c5(8.8, 6.6);
    Complex c9(3.5, 2.0);

    CHECK(c1>c2);
    CHECK(c1<c5);
    CHECK(c1!=c2);
    CHECK(c1==c9);
}


TEST_CASE("Tree Initialization")
{
    SUBCASE("Create a Tree with valid arity")
    {
        // Ensure that the constructor executes without throwing any exceptions
        CHECK_NOTHROW(Tree<int>());
    }

    SUBCASE("Create a Tree with invalid arity")
    {
        CHECK_THROWS(Tree<int>(0));
    }

    SUBCASE("Check defult max children if not set")
    {
        Tree<int> tree;
        CHECK(tree.get_max_children() == 2);
    }
}


TEST_CASE("Tree Root Node")
{
    Tree<int> tree;

    SUBCASE("Add root node")
    {
        Node<int> rootNode(7, 2);
        tree.add_root(rootNode);
        CHECK(tree.begin() != tree.end());
        CHECK((tree.begin())->get_value() == 7);
    }

    SUBCASE("Adding a root to a tree when they have a different maximum number of children")
    {
        Node<int> rootNode(7, 3);
        CHECK_THROWS_AS(tree.add_root(rootNode), invalid_argument);
    }

    SUBCASE("Add second root node throws exception")
    {
        Node<int> rootNode(7, 2);
        tree.add_root(rootNode);
        Node<int> newRootNode(10, 2);
        CHECK_THROWS_AS(tree.add_root(newRootNode), invalid_argument);
    }
}


TEST_CASE("Tree Sub-Nodes") {
    Tree<int> tree;
    Node<int> rootNode(10, 2);
    tree.add_root(rootNode);

    SUBCASE("Add sub-node to existing parent") {
        Node<int> childNode(20, 2);

        // Check if 'add_sub_node' return true
        CHECK(tree.add_sub_node(rootNode, childNode));

        auto it = tree.begin();
        ++it;
        CHECK(it != tree.end());
        CHECK(it->get_value() == 20);
    }

    SUBCASE("Add sub-node to non-existing parent throws exception") {
        Node<int> nonExistentParentNode(15, 2);
        Node<int> childNode(20, 2);
        CHECK_THROWS_AS(tree.add_sub_node(nonExistentParentNode, childNode), runtime_error);
    }

    SUBCASE("Adding a node to a tree when they have a different maximum number of children")
    {
        Node<int> notTheSameMaxChild(7, 3);
        CHECK_THROWS_AS(tree.add_sub_node(rootNode, notTheSameMaxChild), invalid_argument);
    }

    SUBCASE("Add more children than allowed throws exception") {
        Node<int> childNode1(20, 2);
        Node<int> childNode2(30, 2);
        Node<int> childNode3(40, 2);
        tree.add_sub_node(rootNode, childNode1);
        tree.add_sub_node(rootNode, childNode2);
        CHECK_THROWS_AS(tree.add_sub_node(rootNode, childNode3), invalid_argument);
    }
}

TEST_CASE("Binary Tree Traversals") {
    Tree<int> tree;
    Node<int> rootNode(20);
    tree.add_root(rootNode);
    Node<int> leftChild(10);
    Node<int> rightChild(30);
    tree.add_sub_node(rootNode, leftChild);
    tree.add_sub_node(rootNode, rightChild);

    SUBCASE("InOrder Traversal for binary tree") {
        vector<int> in_order_result;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            in_order_result.push_back(it->get_value());
        }
        vector<int> in_order_expected = {10, 20, 30};
        CHECK(in_order_result == in_order_expected);
    }

    SUBCASE("PreOrder Traversal for binary tree") {
        vector<int> pre_order_result;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            pre_order_result.push_back(it->get_value());
        }
        vector<int> pre_order_expected = {20, 10, 30};
        CHECK(pre_order_result == pre_order_expected);
    }

    SUBCASE("PostOrder Traversal for binary tree") {
        vector<int> post_order_result;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            post_order_result.push_back(it->get_value());
        }
        vector<int> post_order_expected = {10, 30, 20};
        CHECK(post_order_result == vector<int>{10, 30, 20});
    }

    SUBCASE("BFS Traversal for binary tree") {
        vector<int> bfs_result;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            bfs_result.push_back(it->get_value());
        }
        vector<int> bfs_expected = {20, 10, 30};
        CHECK(bfs_result == bfs_expected);
    }

    SUBCASE("DFS Traversal for binary tree") {
        vector<int> dfs_result;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            dfs_result.push_back(it->get_value());
        }
        vector<int> dfs_expected = {20, 10, 30};
        CHECK(dfs_result == dfs_expected);
    }

    SUBCASE("Heap order for binary tree") {
        vector<int> heap_order_result;
        for (auto it = tree.myHeap(); it != tree.end_heap(); ++it) {
            heap_order_result.push_back(it->get_value());
        }
        vector<int> heap_order_expected = {10, 20, 30};
        CHECK(heap_order_result == heap_order_expected);
    }
}


TEST_CASE("Testing non-binary tree with naximum children = 4")
{
    Tree<int> tree_ary_tree(4); // 4-ary tree

    Node<int> root(80, 4);
    tree_ary_tree.add_root(root);

    Node<int> child1(20, 4);
    Node<int> child2(30, 4);
    Node<int> child3(40, 4);
    Node<int> child4(50, 4);
    Node<int> child5(60, 4);
    Node<int> child6(70, 4);
    Node<int> child7(10, 4);
    Node<int> child8(90, 4);

    CHECK(tree_ary_tree.add_sub_node(root, child1));
    CHECK(tree_ary_tree.add_sub_node(root, child2));
    CHECK(tree_ary_tree.add_sub_node(root, child3));
    CHECK(tree_ary_tree.add_sub_node(root, child4));
    CHECK(tree_ary_tree.add_sub_node(child1, child5));
    CHECK(tree_ary_tree.add_sub_node(child1, child6));
    CHECK(tree_ary_tree.add_sub_node(child1, child8));
    CHECK(tree_ary_tree.add_sub_node(child6, child7));

    SUBCASE("DFS Traversal for none-binary tree")
    {
        auto it = tree_ary_tree.begin_dfs_scan();
        auto end = tree_ary_tree.end_dfs_scan();

        vector<int> dfs_result;
        while (it != end)
        {
            dfs_result.push_back(it->get_value());
            ++it;
        }

        vector<int> expected_result = {80, 20, 60, 70, 10, 90, 30, 40, 50}; // Expected DFS order
        CHECK(dfs_result == expected_result);
    }

    SUBCASE("BFS Traversal none-binary tree")
    {
        auto it = tree_ary_tree.begin_bfs_scan();
        auto end = tree_ary_tree.end_bfs_scan();

        vector<int> bfs_result;
        while (it != end)
        {
            bfs_result.push_back(it->get_value());
            ++it;
        }

        vector<int> expected_result = {80, 20, 30, 40, 50, 60, 70, 90, 10}; // Expected BFS order
        CHECK(bfs_result == expected_result);
    }

    SUBCASE("In order traversal for none-binary tree")
    {
        // For none-binary tree return a normal DFS scan starting from the root of the tree
        auto it = tree_ary_tree.begin_in_order();
        auto end = tree_ary_tree.end_in_order();

        vector<int> in_order_result;
        while (it != end)
        {
            in_order_result.push_back(it->get_value());
            ++it;
        }

        vector<int> expected_result = {80, 20, 60, 70, 10, 90, 30, 40, 50}; // Expected DFS order
        CHECK(in_order_result == expected_result);
    }

    SUBCASE("Pre order traversal for none-binary tree")
    {
        // For none-binary tree return a normal DFS scan starting from the root of the tree
        auto it = tree_ary_tree.begin_pre_order();
        auto end = tree_ary_tree.end_pre_order();

        vector<int> pre_order_result;
        while (it != end)
        {
            pre_order_result.push_back(it->get_value());
            ++it;
        }

        vector<int> expected_result = {80, 20, 60, 70, 10, 90, 30, 40, 50}; // Expected DFS order
        CHECK(pre_order_result == expected_result);
    }

    SUBCASE("Post order traversal for none-binary tree")
    {
        // For none-binary tree return a normal DFS scan starting from the root of the tree
        auto it = tree_ary_tree.begin_post_order();
        auto end = tree_ary_tree.end_post_order();

        vector<int> post_order_result;
        while (it != end)
        {
            post_order_result.push_back(it->get_value());
            ++it;
        }

        vector<int> expected_result = {80, 20, 60, 70, 10, 90, 30, 40, 50}; // Expected DFS order
        CHECK(post_order_result == expected_result);
    }
}


TEST_CASE("Testing a non binary tree into a heap") {
    Node<double> root(1.1, 3);
    Node<double> child1(2.1, 3);
    Node<double> child2(1.5, 3);
    Node<double> child3(4.3, 3);

    Tree<double> tree(3); // Creating a non-binary tree with k=3
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);

    REQUIRE_THROWS_WITH(tree.myHeap(), "Cannot create heap iterator for non-binary tree"); // This should throw an exception
}


TEST_CASE("Testing tree with complex numbers and non-sorted inserts")
{
    // Tree with complex values and non-sorted inserts
    Tree<Complex> tree;
    Node<Complex> root(Complex(5.5, 6.6));
    tree.add_root(root);

    Node<Complex> n1(Complex(3.3, 4.4));
    Node<Complex> n2(Complex(7.7, 8.8));
    Node<Complex> n3(Complex(1.1, 2.2));
    Node<Complex> n4(Complex(9.9, 1.0));
    Node<Complex> n5(Complex(2.2, 3.3));
    Node<Complex> n6(Complex(4.4, 5.5));

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    SUBCASE("Pre order traversal for tree with complex values")
    {
        vector<Complex> pre_order_result;
        //Pre-order traversal
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            pre_order_result.push_back(node->get_value());
        }
        vector<Complex> pre_order_expected = {Complex(5.5, 6.6), Complex(3.3, 4.4), Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(7.7, 8.8), Complex(2.2, 3.3), Complex(4.4, 5.5)};
        CHECK(pre_order_expected == pre_order_result);
    }

    SUBCASE("Post order traversal for tree with complex values")
    {
        vector<Complex> post_order_result;
        // Post-order traversal
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            post_order_result.push_back(node->get_value());
        }
        vector<Complex> post_order_expected = {Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(3.3, 4.4), Complex(2.2, 3.3), Complex(4.4, 5.5), Complex(7.7, 8.8), Complex(5.5, 6.6)};
        CHECK(post_order_expected == post_order_result);
    }

    SUBCASE("In order traversal for tree with complex values")
    {
        vector<Complex> in_order_result;
        // In-order traversal
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            in_order_result.push_back(node->get_value());
        }
        vector<Complex> in_order_expected = {Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(9.9, 1.0), Complex(5.5, 6.6), Complex(2.2, 3.3), Complex(7.7, 8.8), Complex(4.4, 5.5)};
        CHECK(in_order_expected == in_order_result);
    }

    SUBCASE("Dfs order traversal for tree with complex values")
    {
        vector<Complex> dfs_order_result;
        //Pre-order traversal
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            dfs_order_result.push_back(node->get_value());
        }
        vector<Complex> dfs_order_expected = {Complex(5.5, 6.6), Complex(3.3, 4.4), Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(7.7, 8.8), Complex(2.2, 3.3), Complex(4.4, 5.5)};
        CHECK(dfs_order_expected == dfs_order_result);
    }

    SUBCASE("Bfs order traversal for tree with complex values")
    {
        vector<Complex> bfs_order_result;
        //Pre-order traversal
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            bfs_order_result.push_back(node->get_value());
        }
        vector<Complex> bfs_order_expected = {Complex(5.5, 6.6), Complex(3.3, 4.4), Complex(7.7, 8.8), Complex(1.1, 2.2), Complex(9.9, 1.0), Complex(2.2, 3.3), Complex(4.4, 5.5)};
        CHECK(bfs_order_expected == bfs_order_result);
    }

    SUBCASE("Heap order for tree with complex values")
    {
        vector<Complex> heap_order_result;
        // Heap order traversal
        for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
        {
            heap_order_result.push_back(node->get_value());
        }

        cout << "Heap Order Result:" << endl;
        for (const auto& complex : heap_order_result) {
            cout << complex << endl; // Assuming Complex class has an appropriate output operator
        }

        vector<Complex> heap_order_expected = {Complex(1.1, 2.2), Complex(2.2, 3.3), Complex(3.3, 4.4), Complex(4.4, 5.5), Complex(5.5, 6.6),Complex(9.9, 1.0), Complex(7.7, 8.8)};
        CHECK(heap_order_expected == heap_order_result);
    }
}


TEST_CASE("Testing tree with characters")
{
    Tree<char> tree;
    Node<char> root('A');
    tree.add_root(root);

    Node<char> n1('B');
    Node<char> n2('C');
    Node<char> n3('D');
    Node<char> n4('E');
    Node<char> n5('F');
    Node<char> n6('G');

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    SUBCASE("Pre order traversal for tree with character values")
    {
        vector<char> pre_order_result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            pre_order_result.push_back(node->get_value());
        }
        vector<char> pre_order_expected = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
        CHECK(pre_order_expected == pre_order_result);
    }

    SUBCASE("Post order traversal for tree with character values")
    {
        vector<char> post_order_result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            post_order_result.push_back(node->get_value());
        }
        vector<char> post_order_expected = {'D', 'E', 'B', 'F', 'G', 'C', 'A'};
        CHECK(post_order_expected == post_order_result);
    }

    SUBCASE("In order traversal for tree with character values")
    {
        vector<char> in_order_result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            in_order_result.push_back(node->get_value());
        }
        vector<char> in_order_expected = {'D', 'B', 'E', 'A', 'F', 'C', 'G'};
        CHECK(in_order_expected == in_order_result);
    }

    SUBCASE("Dfs order traversal for tree with character values")
    {
        vector<char> dfs_order_result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            dfs_order_result.push_back(node->get_value());
        }
        vector<char> dfs_order_expected = {'A', 'B', 'D', 'E', 'C', 'F', 'G'};
        CHECK(dfs_order_expected == dfs_order_result);
    }

    SUBCASE("Bfs order traversal for tree with character values")
    {
        vector<char> bfs_order_result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            bfs_order_result.push_back(node->get_value());
        }
        vector<char> bfs_order_expected = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        CHECK(bfs_order_expected == bfs_order_expected);
    }

    SUBCASE("Heap order for tree with character values")
    {
        vector<char> heap_order_result;
        for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
        {
            heap_order_result.push_back(node->get_value());
        }
        vector<char> heap_order_expected = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        CHECK(heap_order_expected == heap_order_result);
    }
}


TEST_CASE("Testing tree with strings")
{
    Tree<string> tree;
    Node<string> root("root");
    tree.add_root(root);

    Node<string> n1("child1");
    Node<string> n2("child2");
    Node<string> n3("grandchild1");
    Node<string> n4("grandchild2");
    Node<string> n5("grandchild3");

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    SUBCASE("Pre order traversal for tree with string values")
    {
        vector<string> pre_order_result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            pre_order_result.push_back(node->get_value());
        }
        vector<string> pre_order_expected = {"root", "child1", "grandchild1", "grandchild2", "child2", "grandchild3"};
        CHECK(pre_order_expected == pre_order_result);
    }

    SUBCASE("Post order traversal for tree with string values")
    {
        vector<string> post_order_result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            post_order_result.push_back(node->get_value());
        }
        vector<string> post_order_expected = {"grandchild1", "grandchild2", "child1", "grandchild3", "child2", "root"};
        CHECK(post_order_expected == post_order_result);
    }

    SUBCASE("In order traversal for tree with string values")
    {
        vector<string> in_order_result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            in_order_result.push_back(node->get_value());
        }
        vector<string> in_order_expected = {"grandchild1", "child1", "grandchild2", "root", "grandchild3", "child2"};
        CHECK(in_order_expected == in_order_result);
    }

    SUBCASE("Dfs order traversal for tree with string values")
    {
        vector<string> dfs_order_result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            dfs_order_result.push_back(node->get_value());
        }
        vector<string> dfs_order_expected = {"root", "child1", "grandchild1", "grandchild2", "child2", "grandchild3"};
        CHECK(dfs_order_expected == dfs_order_result);
    }

    SUBCASE("Bfs order traversal for tree with string values")
    {
        vector<string> bfs_order_result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            bfs_order_result.push_back(node->get_value());
        }
        vector<string> bfs_order_expected = {"root", "child1", "child2", "grandchild1", "grandchild2", "grandchild3"};
        CHECK(bfs_order_expected == bfs_order_result);
    }

    SUBCASE("Heap order for tree with string values")
    {
        vector<string> heap_order_result;
        for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
        {
            heap_order_result.push_back(node->get_value());
        }
        vector<string> heap_order_expected = {"child1", "child2", "grandchild1", "grandchild2", "grandchild3", "root"};
        CHECK(heap_order_expected == heap_order_result);
    }
}