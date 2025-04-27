#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

/**
 * Binary Tree Create
 *
 * Parameters:
 * - int data: the data to be inserted
 * 
 * Returns:
 * - Node*: a referent to the created Node
 */
Node* bt_create(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->left = 0;
    node->right = 0;

    return node;
}

/**
 * Binary Tree Get Height
 *
 * Parameters:
 * - Node* root: the root of the tree
 * 
 * Returns:
 * - int: the height of the tree
 */
int bt_height(Node* root) {
    if (!root) return 0;
    int left = bt_height(root->left);
    int right = bt_height(root->right);

    return 1 + (left > right ? left : right);
}

/**
 * Binary Tree Insert
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - int data: the data to insert
 *
 * Return:
 * - int: 0 on success, -1 on failure
 */
int bt_insert(Node* root, int data) {
    if (!root) return -1;

    Node* node = bt_create(data);

    Node* current;
    Node* tmp[100];
    tmp[0] = root;

    int ptr = 0, end = 1;
    while (ptr != end) {
        current = tmp[ptr++];

        if (current->left == 0) {
            current->left = node;
            return 0;
        } else tmp[end++] = current->left;
        if (current->right == 0) {
            current->right = node;
            return 0;
        } else tmp[end++] = current->right;
    }

    return -1;
}

int bt_delete_node(Node* root, Node* node) {
    if (!root || !node) return -1;
    if (!root->left && !root->right) {
        if (root == node) {
            free(root);
            root = 0;
            return 0;
        } else {
            return -1;
        }
    }
    
    //-- Do stuff™ later, is sleep time now

    return -1;
}

/**
 * Binary Tree Search
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - int data: the data to find
 * 
 * Returns:
 * - Node*: the node of the found data; 0 on failure
 */
Node* bt_search(Node* root, int data) {
    if (!root) return 0;
    if (root->data == data) return root;

    Node* rt = bt_search(root->left, data);
    if (rt) return rt;
    return bt_search(root->right, data);
}

/**
 * Binary Tree Print Tree
 *
 * Parameters:
 * - Node* root: the root of the tree
 */
void bt_print(Node* root) {
    if (!root) return;

    printf("%d ", root->data);
    bt_print(root->left);
    bt_print(root->right);
}

/**
 * Binary Tree Free Tree Memory
 *
 * Parameters:
 * - Node* root: the root of the tree
 */
void bt_free(Node* root) {
    if (!root) return;
    bt_free(root->left);
    bt_free(root->right);

    free(root);
}

//	delete(node) → deletes the node; I vaguely recall that you want to replace it with the right-most node, so that's what I'll do


void print_debug(Node* root) {
    if (!root) return;
    printf("%p (%d):\t%p (%d)\t%p (%d)\n",
            root,
            root->data,
            root->left,
            (root->left ? root->left->data : 0),
            root->right,
            (root->right ? root->right->data : 0)
            );
}

int main() {
    Node* root = bt_create(1);
    bt_insert(root, 2);
    bt_insert(root, 3);
    bt_insert(root, 4);
    bt_insert(root, 5);
    bt_insert(root, 6);
    bt_insert(root, 7);
    bt_insert(root, 8);
    bt_insert(root, 9);
    bt_insert(root, 10);
    bt_insert(root, 11);
    bt_print(root);

    bt_free(root);
}
