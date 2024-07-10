// 207723198
// yair852258@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

using namespace std;

template <typename T>
class Node {
public:
    /**
     * @brief Constructs a Node with a given value.
     * @param val The value to be stored in the node.
     * @param max_children The maximum number of children each vertex can have
     */
    explicit Node(const T& val, size_t max_children = 2):
                 value(val), max_children(max_children), current_children_Num(0), destroyed(false) {}

    /**
     * @brief Constructs a Node copy with a given node.
     * @param other the copied node.
     */
    Node(const Node<T>& other):
                 value(other.value), max_children(other.max_children),current_children_Num(other.current_children_Num), children(other.children), destroyed(false){}

    /**
     * @brief Gets the value stored in the node.
     * @return The value of type T.
     */
    T get_value() const
    {
     return this->value;
    }

 /**
  * @brief Gets the maximum number of children each vertex can have
  * @return The value of type T.
  */
    size_t get_max_children() const
    {
      return max_children;
    }

    /**
     * @brief Gets the number of childrens of the node.
     * @return The number of the childrens.
     */
    size_t get_current_children() const
    {
     return this->current_children_Num;
    }

    /**
     * @brief Gets the children of the node.
     * @return A constant reference to a vector of pointers to the node's children.
     */
    const vector<Node*>& get_children() const
    {
     return this->children;
    }

    /**
     * @brief Adds a child to the node.
     *
     * This method adds a child node to the vector of children. It checks for various conditions
     * to ensure the integrity of the tree structure.
     *
     * @param child A pointer to the child node to be added.
     * @throws std::runtime_error if the child is null, the maximum number of children is exceeded,
     *         or the child node type does not match.
     */
    bool add_child(Node<T>* child)
    {
     if(!child || (current_children_Num == max_children) || (typeid(*child) != typeid(Node<T>)))
     {
      return false;
     }
     current_children_Num++;
     children.push_back(child);
     return true;
    }

    /**
     * @brief Sets a child at a specific index.
     *
     * This method replaces the child node at the specified index with a new child node.
     *
     * @param index The index at which the child node should be set.
     * @param child A pointer to the new child node.
     * @throws std::out_of_range if the index is out of range of the children vector.
     */
    void set_child(size_t index, Node<T>* child)
    {
     if (index >= current_children_Num)
     {
      throw out_of_range("Index out of range");
     }
     children[index] = child;
    }

private:
    T value; ///< The value stored in the node.
    size_t max_children; ///< The maximum number of children each vertex can have
    size_t current_children_Num; ///< The current number of children this node has
    std::vector<Node*> children; ///< Pointers to the children nodes.
    bool destroyed; ///< Indicates whether the node is destroyed.
};

#endif //NODE_HPP

