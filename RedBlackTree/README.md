# Red-Black Tree

A **Red-Black Tree** is a type of self-balancing binary search tree (BST).  The red-black tree ensures that the tree remains balanced during insertions and deletions by following a set of properties. This guarantees that the tree height remains logarithmic relative to the number of nodes, ensuring optimal search, insertion, and deletion times-O(log n) in the worst case.

## Key Properties of a Red-Black Tree

1. **Node Color**: Each node is either red or black.
1. **Root Property**: The root node is always black.
1. **Leaf Property**: Every leaf (NIL node) is black.
1. **Red Property**: Red nodes cannot have red children (no two consecutive red nodes).
1. **Black Height Property**: Every path from a given node to its descendant NIL nodes must contain the same number of black nodes.

## Operations

### 1. **Insertion**
    - When a new node is inserted, it is always colored **red**.
    - After insertion, the tree may violate the red-black properties, which can be fixed using **rotations** and **recoloring**.

### 2. **Deletion**
    - Similar to insertion, deletion can violate the properties of the tree, which are corrected using **rotations**, **recoloring**, and **restructuring** the tree.
