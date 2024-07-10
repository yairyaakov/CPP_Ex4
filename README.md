# Generic Tree Data Structure Project

**Assignment: Tree and Node Implementation**  
**Email: yair852258@gmail.com**

## Overview

This project provides a flexible implementation of a generic tree data structure in C++, supporting customizable arity and various traversal methods. It includes visualization capabilities using the SFML library for graphical representation.

## Features

- **Generic Tree Implementation**: Supports customizable arity.
- **Tree Traversals**:
  - In-order (for binary trees)
  - Pre-order (for binary trees)
  - Post-order (for binary trees)
  - Breadth-First Search (BFS)
  - Depth-First Search (DFS)
  - Heap (additional traversal method)
- **SFML Visualization**: Visualize the tree structure using the SFML library.

## Dependencies

- **SFML**: Simple and Fast Multimedia Library for visualization.
- **doctest**: Lightweight testing framework for C++.

## Usage

### Running the Game

To compile and run the project, use the following command:

```bash
make tree
```
This command compiles the project and executes the main tree application.

### Running Tests

To run tests, use the following command:

```bash
make runtests
```
This command executes all unit tests to ensure the correctness of the tree implementation.

### Cleaning Up Files

To delete files created during compilation and execution, use the following command:

```bash
make clean
```
This command removes executable files and object files, leaving the directory clean.
