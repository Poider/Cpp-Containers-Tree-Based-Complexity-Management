# Creating Complex Tree-Based Advanced Data Structures

This repository contains a collection of custom, high-performance tree-based data structures implemented from scratch, designed to help users understand the low-level workings of these structures. These structures are built to rival the performance of the C++ standard library containers, offering alternatives that perform better in specific use cases.

## Overview
The goal of this project is to create complex, efficient data structures from scratch using **AVL trees** and **Red-Black trees**. These trees are used as the foundational balancing mechanisms for the custom implementations of the following data structures:
- **Map**
- **Set**
- **Vector**
- **Stack**

Each data structure is implemented with all necessary utilities, functions, iterators, and supporting tools, providing a complete and functional library to understand how these structures work at a low level.

## Features
- **Custom Implementations:** Data structures like `map`, `set`, `vector`, and `stack` have been implemented from scratch, taking inspiration from C++ reference materials and standard libraries. All necessary utility functions, iterators, and auxiliary tools are included to ensure full functionality.
- **Low-Level Understanding:** Aiming to provide a deeper understanding of how these complex data structures work under the hood, this project highlights their internal mechanics and interactions.
- **Balanced Trees for Optimization:** Both AVL and Red-Black trees are utilized to balance data and improve performance. These trees are central to the internal implementation of the `map` and `set`, ensuring efficient access and modification.
- **Complete Functionality:** The implementations come with fully functional iterators, search and insertion functions, deletion, traversal methods, and utilities like size tracking and element access.
- **Performance Comparison:** The data structures in this project are benchmarked against the C++ standard containers, showcasing competitive performance in terms of speed and memory usage.

## Implemented Data Structures
1. **Map**  
   - Stores key-value pairs.
   - Uses AVL and Red-Black trees for balancing to ensure efficient lookup, insertion, and deletion.
   - Fully supports iterators, insertions, deletions, and access to keys and values.

2. **Set**  
   - A collection of unique elements, automatically sorted.
   - Leverages AVL and Red-Black trees for efficient element insertion and retrieval.
   - Includes complete iterator support for traversal and element management.

3. **Vector**  
   - A dynamic array that allows random access to elements.
   - Optimized for efficient resizing and access, and includes utilities for insertion, deletion, and access.

4. **Stack**  
   - A last-in, first-out (LIFO) structure for handling data.
   - Provides efficient push and pop operations, with full iterator support for easy traversal.

## Usage
To compile and use the project:

```bash
make
```

Example usage:

```cpp
#include "your_custom_ds.h"

int main() {
    Map<int, std::string> map;
    map.insert(1, "One");
    map.insert(2, "Two");

    std::cout << map[1] << std::endl;  // Output: One
    return 0;
}
```
- A couple main functions are provided to ease the testing

## Performance Benchmarks
- This repository includes performance benchmarks comparing the AVL and Red-Black tree-based data structures with their C++ standard library counterparts.
- Results demonstrate that, in some cases, the custom implementations outperform the default C++ containers due to tailored optimizations.

## Why This Project?
The purpose of this project is not just to implement these data structures but to provide an in-depth look at how they work, including all their utilities, functions, and iterators. It aims to help developers understand the complexities involved in building their own library of data structures and how these internal components interact to provide high-level functionality.

## How to Contribute
If you'd like to contribute or suggest improvements:
1. Fork the repository.
2. Create a feature branch.
3. Commit your changes and submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
