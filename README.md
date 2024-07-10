Generic Tree Data Structure Project
Overview

This project provides a flexible implementation of a generic tree data structure in C++, supporting customizable arity and various traversal methods. It includes visualization capabilities using the SFML library for graphical representation.
Features

    Generic Tree Implementation: Supports trees with customizable arity.
    Traversal Methods:
        In-order (for binary trees)
        Pre-order (for binary trees)
        Post-order (for binary trees)
        Breadth-First Search (BFS)
        Depth-First Search (DFS)
        Heap (additional traversal method)
    SFML Visualization: Utilizes SFML for visual representation of tree structures.

Dependencies

    SFML: Simple and Fast Multimedia Library for visualization.
    doctest: Lightweight testing framework for C++.

Usage
Running the Project

To compile and run the project, use the following command:
make tree
This command compiles the project and executes the main tree application.

Running Tests

To run tests for the project, use the following command:
make runtests
This command executes all unit tests to ensure the correctness of the tree implementation.

Cleaning Up

To clean up files generated during compilation and execution, use:
make clean
This command removes executable files and object files, leaving the directory clean.
