# Data Structures
How I would implement these data structures. Not necessarily the best implementations; I would posit that they'll probably be a bare bone, lowest common denominator, kind of data structure.

# Linked List
The one, the only, classic data structure taught to basically anyone that does an algorithms and data structure course.
From what I understand, a Linked List is terrible for memory as it's non-contiguous, but great for inserting/removing elements— this is compared to your basic arrays.

The structure looks something like:

Node { data, next *Node }

Then you would keep a reference to the head node.

The thing's surrounding methods are something like:
- create(data) → creates a node with data
- insert(data, position) → insert new data at position
    - Can change the list head, thus it returns the head of the list
- append(data) → insert new data at the end
- append(Node) → append a Node
- get(position) → get the data from the position-th node
- delete(position) → deletes the position-th node
    - Can change the list head, thus it returns the head of the list
- delete() → deletes the list
- print() → prints the list

# Binary Tree
Your classic tree. You have a head node with 2 child nodes. It's... well, a tree. There's no rhyme or reason to where you add nodes, usually just to the next available child. You could implement rules for this insertion, but that gets us to other trees, like a Binary Search Tree. The classic Binary Tree inserts left to right on a layer until there's no spots left, then moves down a layer.

The structure looks something like:

Node { data, left *Node, right *Node }

And you keep a reference to the head node.

The exposed methods would be something like:
- create(data) → creates a node with data and empty children
- insert(data) → inserts data into the next available position
- search(data) → find an occurance of data; returns the node
- delete(node) → deletes the node; I vaguely recall that you want to replace it with the bottom-right-most node, so that's what I'll do
- height() → traverse the left-most branch, return the number of nodes
- delete() → deletes the tree
- print() → prints the tree

# Binary Search Trees
Binary Search Trees, just as classic as the Linked List. You have a node that branches out to two child nodes, that branch out to two child nodes, that branch out... you can implement a Binary Search Tree on an array (if you like pain) and it, by nature of its design, implements a divide and conquer approach to its storage— Kinda. That is, you have a head node with a given value, if you add a value less than that value, you insert it to the left child (repeating the process as necessary) and if it's larger than the value, you insert it to the right child.

The structure looks something like:

Node { data, left *Node, right *Node }

And you keep a reference to the head node.

The exposed methods should be something like:
- create(data) → creates a node with data and empty children
- insert(data) → inserts data into the tree
- search(data) → returns the node of the data, if it exists
- delete(data) → deletes the data from the tree, if it exists
- min() → returns the lowest data point in the tree
- max() → returns the highest data point in the tree
- print() → prints the tree
- delete() → deletes the tree

