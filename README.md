# AstroTree Description

The Romanian Space Agency has proposed to develop its own satellite network in order to observe and explore space. 
The satellite network must be implemented in the form of a binary tree. The satellites are interconnected, and there 
is a root satellite, located close to Earth’s atmosphere, which connects to all the other satellites

# About 

The project implements a binary tree of satellites using multiple data structures (MinHeap, queue, stack).

# Structures:

- Satellite stores frequency and name
- TreeNode represents a binary tree node (satellite + child pointers).
- MinHeap stores tree nodes, ordered by priority (frequency, then name).
- Queue and stack structures are defined for BFS and DFS traversals, the stack including a path field for encoding.

# Main flow (tema2.c):

- Reads the number of satellites and builds an array of Satellite structures
- Inserts nodes into a MinHeap and repeatedly extracts the two smallest nodes to construct the binary tree with buildNod.
- The last node in the MinHeap becomes the tree root.

# Functions (biblioteca.c):
Depending on the task number, different functions are executed.

- Task 1: Implements MinHeap operations (Insert, ExtractMin, SiftUp, SiftDown) and BFS traversal (enqueue, dequeue, printBFS) to print the tree level by level.
- Task 2: Traverses the tree according to a binary code (0 → left, 1 → right) and outputs the satellite name at the reached leaf.
- Task 3: Uses DFS with a stack to compute binary encodings for given satellite names, storing and updating the path during traversal.
- Task 4: Performs DFS to find the lowest common ancestor of a given set of satellites by checking if their names appear under the same parent node.
