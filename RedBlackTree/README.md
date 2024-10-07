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
    - Much more complicated then insertion.

## Thinking

There are some topic worth thinking when implementing **red-black tree**.

- using recursive approach or iterative approach
- how to pass root pointer, by returning the root or pass address of root as function parameters
- when it comes to deletion, there are two approaches when the target node has two child nodes. By deleting the original target and make some pointer changes or assigning the successor value to target node and then delte the successor node. Both approachs end up with a valid red-black tree

1. Change the value of the target node to its successor:

  - How it works:
    - Find the in-order successor (smallest node in the right subtree) of the node to be deleted.
    - Instead of deleting the target node itself, copy the value of the successor into the target node.
    - Now, you need to delete the successor, which is either a leaf node or has at most one child. Deleting this node is staightforward compared to deleting the original node with two children.
  - Advantages:
    - The structure of the tree is not heavily modified; only the value is changed.
    - The deletion problem is reduced to the easier case of deleting a node with at most one child.
  - Disadvantages:
    - It may seem less intuitive as the "target" node is not actually removed, but its value is replaced.
    - If your data structure relies on pointers to specific nodes (not just values), this might cause inconsistencies.
2. Change the node (pointer) itself to point to the successor:
   - How it works:
     - Directly remove the target node by replacing it with its in-order successor. The successor node is "moved" to the location of the node to be deleted.
     - This involves updateing the tree structure by changeing parent-child pointers so that the successor takes the place of the target node.
     - As in the first approach, you still need to handle the deletion of the successor's original location (which has at most one child).
   - Advantages:
     - This method is more direct and intuitive, as the node itself is replaced.
     - It can be easier or manage if the code or data structure relies on node references/pointers rather than just values.
   - Disadvantages:
     - This can cause more changes in the tree structure (i.e., pointers updates) compared to the value-replacement approach, which may be slightly more complex to implement.

## Reference

- [postgreSql Red Black Tree rbtree.h](https://github.com/postgres/postgres/blob/master/src/include/lib/rbtree.h)
- [postgreSql Red Black Tree rbtree.c](https://github.com/postgres/postgres/blob/master/src/backend/lib/rbtree.c)