// 207723198
// yair852258@gmail.com

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <iostream>          // For input-output stream
#include "Node.hpp"
#include <SFML/Graphics.hpp> // For tree visualization
#include <sstream>           // For string stream

using namespace std;
using namespace  sf;

template<typename T>
class Tree {
public:
    explicit Tree(size_t max_children = 2) : root(nullptr), hasRoot(false), max_children(max_children)
    {
        if (max_children <= 0) {
            throw runtime_error("Tree arity must be greater than 0");
        }
    }

    // Destructor
    ~Tree()
    {
        clear(this->root);
    }

    size_t get_max_children() const
    {
        return max_children;
    }

    void clear(Node<T>* node)
    {
        if(node)
        {
            for(auto child : node->get_children())
            {
                clear(child);
            }
            delete node;
        }
    }

    void add_root(const Node<T>& rootNode)
    {
        if (this->hasRoot)
        {
            throw invalid_argument("Root already exists");
        }

        if (rootNode.get_max_children() != this->max_children)
        {
            throw invalid_argument("This Root and this tree have a different maximum number of children.");
        }

        // Initialize root with k children
        root = new Node<T>(rootNode.get_value(), this->max_children);
        hasRoot = true;
    }

    bool add_sub_node(const Node<T>& parentNode, const Node<T>& childNode)
    {
        if (!hasRoot)
        {
            throw invalid_argument("Tree has no root.");
        }

        if (childNode.get_max_children() != parentNode.get_max_children())
        {
            throw invalid_argument("This node and this tree have a different maximum number of children.");
        }

        if (Node<T>* parent = find_node(root, parentNode.get_value()))
        {
            // Initialize child node with the maximum children of each node in the tree
            Node<T>* child = new Node<T>(childNode.get_value(), this->max_children);
            // Add child to parent node if found
            if (parent->add_child(child))
            {
                return true;
            }
            // Clean up if add_child fails
            delete child;
            throw invalid_argument("Cannot add the child to the parent node.");
        }
        throw runtime_error("Parent node not found."); // Throw error if parent node not found
    }

    // Class for iterators to BFS and DFS
    class Iterator {
    public:
        enum TraversalType { DFS, BFS };

        Iterator(Node<T>* rootNode, TraversalType type): traversalType(type)
        {
            if(rootNode)
            {
                if(BFS == type)
                {
                    this->bfsQueue.push(rootNode);
                }
                else if(DFS == type)
                {
                    this->dfsStack.push(rootNode);
                }
            }
        }

        Iterator(const Iterator& other):
                            dfsStack(other.dfsStack), bfsQueue(other.bfsQueue), traversalType(other.traversalType) {}

        bool operator!=(const Iterator& other) const
        {
            if (traversalType != other.traversalType) return true;

            if (traversalType == DFS) {
                if (dfsStack.empty() && other.dfsStack.empty()) return false;
                if (dfsStack.empty() || other.dfsStack.empty()) return true;
                return dfsStack.top() != other.dfsStack.top();
            }
            // If (traversalType == BFS)
            if (bfsQueue.empty() && other.bfsQueue.empty()) return false;
            if (bfsQueue.empty() || other.bfsQueue.empty()) return true;
            return bfsQueue.front() != other.bfsQueue.front();
        }

        bool operator==(const Iterator& other) const
        {
            return !(*this != other);
        }

        Node<T>& operator*()
        {
            if (traversalType == DFS)
            {
                return *dfsStack.top();
            }
            // If (traversalType == BFS)
            return *bfsQueue.front();
        }

        Node<T>* operator->()
        {
            if (traversalType == DFS)
            {
                return dfsStack.top();
            }
            // If (traversalType == BFS)
            return bfsQueue.front();
        }

        Iterator& operator++()
        {
            if (traversalType == DFS) {
                Node<T>* current = dfsStack.top();
                dfsStack.pop();
                // Push children in reverse order for correct left-to-right DFS
                for (auto child = current->get_children().rbegin(); child != current->get_children().rend(); ++child) {
                    if (*child)
                    {
                        dfsStack.push(*child);
                    }
                }
            }
            else
            {
                Node<T>* current = bfsQueue.front();
                bfsQueue.pop();
                for (auto child : current->get_children())
                {
                    if (child)
                    {
                        bfsQueue.push(child);
                    }
                }
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        stack<Node<T>*> dfsStack;
        queue<Node<T>*> bfsQueue;
        TraversalType traversalType;
    };

    //End iterator class

    Iterator begin()
    {
        return Iterator(this->root, Iterator::BFS); // Default iterator is BFS starting at root
    }

    Iterator end()
    {
        return Iterator(nullptr, Iterator::BFS); // Default iterator is BFS at end
    }

    Iterator begin_dfs_scan()
    {
        return Iterator(this->root, Iterator::DFS); // Return iterator starting at root
    }

    Iterator end_dfs_scan()
    {
        return Iterator(nullptr, Iterator::DFS); // Return iterator at end
    }

    Iterator begin_bfs_scan()
    {
        return Iterator(this->root, Iterator::BFS); // Return iterator starting at root
    }

    Iterator end_bfs_scan()
    {
        return Iterator(nullptr, Iterator::BFS); // Return iterator at end
    }


    // Pre-order iterator. The same algoritem for pre order and dfs
    class pre_order_iterator
    {
    public:
        explicit pre_order_iterator(Node<T> *rootNode)
        {
            if (rootNode)
                nodesStack.push(rootNode); // Initialize with root node
        }

        bool operator!=(const pre_order_iterator &other) const
        {
            if (nodesStack.empty() && other.nodesStack.empty()) return false;
            if (nodesStack.empty() || other.nodesStack.empty()) return true;
            return nodesStack.top() != other.nodesStack.top();
        }

        Node<T> &operator*() const
        {
            return *nodesStack.top(); // Dereference top node in stack
        }

        Node<T> *operator->() const
        {
            return nodesStack.top(); // Return top node in stack
        }

        pre_order_iterator &operator++()
        {
            Node<T> *current = nodesStack.top();
            nodesStack.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
            {
                if (*it != nullptr)
                    nodesStack.push(*it); // Push children to stack in reverse order
            }
            return *this;
        }

        pre_order_iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        stack<Node<T> *> nodesStack; // Stack for nodes
    };

    //End pre_order_iterator class


    pre_order_iterator begin_pre_order() const
    {
        return pre_order_iterator(this->root); // Return iterator starting at root
    }

    pre_order_iterator end_pre_order() const
    {
        return pre_order_iterator(nullptr); // Return iterator at end
    }


    // Post-order iterator
    class Post_order_iterator
    {
    public:
        explicit Post_order_iterator(Node<T> *rootNode, size_t max_children) : currentNode(nullptr), max_children(max_children)
        {
            if (rootNode)
            {
                // Binary tree traversal
                if (max_children==2)
                {
                    push_left_Most(rootNode); // Push leftmost path for binary trees
                }

                // Dfs traversal for General tree
                else
                {
                    nodesStack.push(rootNode); // Push root node for general trees
                }
            }
            ++(*this); // Move to the first valid node
        }

        bool operator!=(const Post_order_iterator &other) const
        {
            return currentNode != other.currentNode; // Check if current node is not the same as other's current node
        }

        Node<T> *operator->() const
        {
            return currentNode; // Return current node
        }

        Node<T> &operator*() const
        {
            return *currentNode; // Dereference current node
        }

        Post_order_iterator &operator++()
        {
            if (max_children == 2)
            {
                // Binary tree traversal
                if (!nodesStack.empty())
                {
                    Node<T> *node = nodesStack.top();
                    nodesStack.pop();

                    // If the stack is not empty, check the parent node
                    if (!nodesStack.empty())
                    {
                        Node<T> *parent = nodesStack.top();
                        // If the current node is the left child, push the leftmost path of the right child
                        if (parent->get_children().size() > 1 && node == parent->get_children()[0])
                        {
                            push_left_Most(parent->get_children()[1]);
                        }
                    }
                    // Update the current node to the node that was just popped
                    currentNode = node;
                }
                else
                {
                    // End iteration if stack is empty
                    currentNode = nullptr;
                }
            }
            else
            {
                // Dfs traversal for General tree
                if (!nodesStack.empty())
                {
                    Node<T> *node = nodesStack.top();
                    nodesStack.pop();

                    // Push children of the current node in reverse order
                    for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it)
                    {
                        if (*it)
                        {
                            nodesStack.push(*it);
                        }
                    }
                    // Update the current node to the node that was just popped
                    currentNode = node;
                }
                else
                {
                    // End iteration if stack is empty
                    currentNode = nullptr;
                }
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        stack<Node<T> *> nodesStack; // Stack for nodes
        Node<T> *currentNode;                 // Current node
        size_t max_children;              // Maximum number of children

        void push_left_Most(Node<T> *node)
        {
            while (node)
            {
                nodesStack.push(node);
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0]; // Push leftmost children
                }
                else
                {
                    break;
                }
            }
        }
    };
    //End Post_order_iterator class

    Post_order_iterator begin_post_order() const
    {
        return Post_order_iterator(root, this->max_children); // Return iterator starting at root
    }

    Post_order_iterator end_post_order() const
    {
        return Post_order_iterator(nullptr, this->max_children); // Return iterator at end
    }


    // In-order iterator
    class in_order_iterator
    {
    public:
        explicit in_order_iterator(Node<T> *rootNode, size_t max_children) : max_children(max_children)
        {
            if (rootNode)
            {
                // Binary tree traversal
                if (max_children == 2)
                {
                    push_left_Most(rootNode); // Push leftmost path for binary trees
                }
                // Dfs traversal for General tree
                else
                {
                    nodesStack.push(rootNode); // Push root node for general trees
                    while (!nodesStack.empty() && !nodesStack.top())
                        nodesStack.pop();
                }
            }
        }

        bool operator!=(const in_order_iterator &other) const
        {
            return !nodesStack.empty() != !other.nodesStack.empty(); // Check if nodes stack is not empty
        }

        Node<T> *operator->() const
        {
            return nodesStack.top(); // Return top node in stack
        }

        Node<T> &operator*() const
        {
            return *nodesStack.top(); // Dereference top node in stack
        }

        in_order_iterator &operator++()
        {
            if (nodesStack.empty())
                return *this;

            // Binary tree traversal
            if (max_children == 2)
            {
                Node<T> *node = nodesStack.top();
                nodesStack.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr)
                {
                    push_left_Most(node->get_children()[1]); // Push leftmost path for right child
                }
            }
            // Dfs traversal for General tree
            else
            {
                Node<T> *current = nodesStack.top();
                nodesStack.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it)
                {
                    if (*it != nullptr)
                        nodesStack.push(*it); // Push children in reverse order
                }
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        stack<Node<T> *> nodesStack; // Stack for nodes
        size_t max_children;                    // Maximum number of children

        void push_left_Most(Node<T> *node)
        {
            while (node)
            {
                nodesStack.push(node);
                if (!node->get_children().empty())
                {
                    node = node->get_children()[0]; // Push leftmost children
                }
                else
                {
                    break;
                }
            }
        }
    };
    //End in_order_iterator class

    in_order_iterator begin_in_order() const
    {
        return in_order_iterator(root, this->max_children); // Return iterator starting at root
    }

    in_order_iterator end_in_order() const
    {
        return in_order_iterator(nullptr, this->max_children); // Return iterator at end
    }


    // Heap iterator
    class heap_iterator
    {
    public:
        explicit heap_iterator(Node<T> *rootNode, size_t max_children) : max_children(max_children)
        {
            if (max_children != 2)
            {
                throw runtime_error("Cannot create heap iterator for non-binary tree"); // Throw error if tree is not binary
            }
            if (rootNode)
            {
                collect_nodes(rootNode);                                                   // Collect all nodes for heap
                make_heap(nodesHeap.begin(), nodesHeap.end(), CompareNodes()); // Create a heap
            }
        }

        bool operator!=(const heap_iterator &other) const
        {
            return !nodesHeap.empty() != !other.nodesHeap.empty(); // Check if heap is not empty
        }

        Node<T> *operator->() const
        {
            return nodesHeap.front(); // Return front node in heap
        }

        Node<T> &operator*() const
        {
            return *nodesHeap.front(); // Dereference front node in heap
        }

        heap_iterator &operator++()
        {
            if (!nodesHeap.empty())
            {
                pop_heap(nodesHeap.begin(), nodesHeap.end(), CompareNodes()); // Remove front node
                nodesHeap.pop_back();
            }
            return *this;
        }

        heap_iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        vector<Node<T> *> nodesHeap; // Vector for heap nodes
        size_t max_children;               // Maximum number of children

        struct CompareNodes
        {
            bool operator()(Node<T> *a, Node<T> *b)
            {
                return a->get_value() > b->get_value(); // Compare nodes by value
            }
        };

        void collect_nodes(Node<T> *node)
        {
            if (node)
            {
                nodesHeap.push_back(node); // Collect current node
                for (auto child : node->get_children())
                {
                    collect_nodes(child); // Recursively collect children nodes
                }
            }
        }
    };
    // End Heap iterator class

    heap_iterator myHeap() const
    {
        return heap_iterator(root, this->max_children); // Return heap iterator starting at root
    }

    heap_iterator end_heap() const
    {
        return heap_iterator(nullptr, this->max_children); // Return heap iterator at end
    }

//method to show the tree GUI using sfml

void print() {
    //set the screen and the font of the GUI
    RenderWindow screen(VideoMode(800, 600), "tree GUI");
    Font font;
    if (!font.loadFromFile("./arial.ttf")) {
        cerr << "error in font loading" << endl;
        return;
    }

    // set the screen with a white color (clear)
    screen.clear(Color::White);
    // draw the tree in the screen starting from the root node at the position (350, 20) with a space of 600/k between nodes in the same level
    drawTree(screen, font, root, 350, 20, 150);
    // display the screen after the drawing of the tree
    screen.display();

    // loop to keep the GUI screen open until the user press the close button of the screen or escape in the keyboard
    while (screen.isOpen()) {
        Event event;
        // update the event based on what the user did
        while (screen.pollEvent(event)) {
            // check if the user pressed the close button of the screen
            if (event.type == Event::Closed) {
                // clear the screen and close it
                screen.clear(Color::White);
                screen.close();
            }
            // check if the user pressed the escape key in the keyboard
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    // clear the screen and close it
                    screen.clear(Color::White);
                    screen.close();
                }
            }
        }
    }
}





// method to draw the tree in the GUI
//get screen,font,node to start from,starting x,starting y,spacing between the nodes
void drawTree(RenderWindow& screen, Font& font, Node<T>* node, float x, float y, float spaceBetweenNodes) {
    // if the node is null, return and dont draw
    if (!node) {
        return;
    }

    // draw the circle representing the node
    CircleShape circle(35); // set the circle with it radius
    circle.setPosition(x, y); // set the position of the node
    circle.setFillColor(Color::Blue);// set blue as the color of the node
    screen.draw(circle);// draw the node on the screen

    // take the value of the node and represent it as string
    T value = node->get_value();
    ostringstream oss;
    oss << value; // convert the value to a string
    string valueAsString = oss.str(); // save the string representation of the value of the node

    // draw the value of the node inside the node circle
    Text valueToDraw(valueAsString, font, 25);// create a Text object with the node value, font, and font size 25
    valueToDraw.setFillColor(Color::Black); // color of the value of the node
    FloatRect textBounds = valueToDraw.getLocalBounds();// get the bounds of the Text object for centering the string in the node
    valueToDraw.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);//set the text to the center of its bounds
    valueToDraw.setPosition(x + circle.getRadius(), y + circle.getRadius());// position the value in the center of the circle
    screen.draw(valueToDraw);//draw the value of the node on the screen

    // draw lines that represents the edges of the node to its children
        auto children = node->get_children();
        size_t num_of_children = node->get_current_children();  // the number of children of the node

    if (num_of_children > 0) {  // if the node has children
        for (size_t i = 0; i < num_of_children; i++) {  //  loop for each child
            float xOfChild = (x - spaceBetweenNodes / 2) + (i * spaceBetweenNodes);  // calculate the x position of the child node
            float yOfChild = y + 100;  // calculate the y position of the child node
            Vertex edge[] = {  // create an edge from the parent node to the child node
                    Vertex(Vector2f(x + circle.getRadius(), y + circle.getRadius() * 2)),  // the starting point of the edge
                    Vertex(Vector2f(xOfChild + circle.getRadius(), yOfChild))  // the ending point of the edge
            };
            edge[0].color = Color::Black;  // set the color of the starting point of the edge
            edge[1].color = Color::Black;  // set the color of the ending point of the edge
            screen.draw(edge, 2, Lines);  // draw the edge on the screen
            drawTree(screen, font, children[i], xOfChild, yOfChild, spaceBetweenNodes / 2);  // draw the child node and its subtree
        }
    }
}


private:
    Node<T>* root;
    bool hasRoot;
    size_t max_children; ///< The maximum number of children each vertex can have

    // Find given node in the tree
    Node<T>* find_node(Node<T>* current, const T &value) const
    {
        if(current == nullptr){return nullptr;}

        if(current->get_value() == value){return current;}

        for(auto child : current->get_children())
        {
            Node<T>* result = find_node(child, value);
            if (result)
            {
                return result;
            }
        }

        return nullptr;
    }
};

#endif // TREE_H
