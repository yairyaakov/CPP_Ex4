#include <iostream>
#include "Node.hpp"
#include "Tree.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    Tree<double> tree; // Default to binary tree that contains doubles.

    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "traversal the binary tree:" << endl;
    cout << "Pre-order traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "\nPost-order traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "\nIn-order traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "\nBFS scan traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\nRange-based for loop (BFS):" << endl;
    for (auto node : tree) {
        cout << node.get_value() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\nDFS scan traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.4 1.5 1.3 1.6

    cout << "\nHeap traversal:" << endl;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    tree.print();


    Tree<double> three_ary_tree(3); // 3-ary tree

    Node<double> three_ary_root(1.1, 3);
    three_ary_tree.add_root(three_ary_root);

    Node<double> n6(1.2, 3);
    Node<double> n7(1.3, 3);
    Node<double> n8(1.4, 3);
    Node<double> n9(1.5, 3);
    Node<double> n10(1.6, 3);

    three_ary_tree.add_sub_node(three_ary_root, n6);
    three_ary_tree.add_sub_node(three_ary_root, n7);
    three_ary_tree.add_sub_node(three_ary_root, n8);
    three_ary_tree.add_sub_node(n6, n9);
    three_ary_tree.add_sub_node(n7, n10);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    cout << "\n";
    cout << "\ntraversal the three ary tree:" << endl;
    cout << "Pre-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    cout << "\nPost-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    cout << "\nIn-order traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    cout << "\nBFS scan traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\nRange-based for loop (3-ary tree):" << endl;
    for (const auto& node : three_ary_tree) {
        cout << node.get_value() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "\nDFS scan traversal (3-ary tree):" << endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1 1.2 1.5 1.3 1.6 1.4

    cout << "\nHeap traversal:" << endl;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node) {
        cout << node->get_value() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout<<"\n";
    three_ary_tree.print();

    return 0;
}
