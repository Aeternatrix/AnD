#include <stdio.h>
#include <stdlib.h>

#define BIG 100

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
 * - Node*: a reference to the created Node
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

/* 
 * Helper Function
 */
static
void bt_deepest_right_node(Node* root, Node** result, Node** parent) {
    Node* tmp[BIG];
    tmp[0] = root;
    int ptr = 0, end = 1;
    while (ptr != end) {
        *result = tmp[ptr++];
        if ((*result)->left != 0) tmp[end++] = (*result)->left;
        if ((*result)->right != 0) tmp[end++] = (*result)->right;
    }
    *parent = tmp[(end >> 1) - 1];
}

/**
 * Binary Tree Delete Node
 *
 * Note:
 * - If the node targetted for deletion is in a different tree, it will delete the node from the root tree and copy it over the node tree
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - Node* data: the data node to delete
 * 
 * Returns:
 * - int: -1 on failure; 0 on success
 */
int bt_delete(Node* root, Node* node) {
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
    Node* parent;
    Node* replacement;
    bt_deepest_right_node(root, &replacement, &parent);
    node->data = replacement->data;
    if (parent->right == replacement) parent->right = 0;
    if (parent->left == replacement) parent->left = 0;
    free(replacement);
    return 0;
}

/**
 * Binary Tree Search by Data
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

static
void bt_print_helper(Node* root) {
    if (!root) return;

    printf("%d ", root->data);
    bt_print_helper(root->left);
    bt_print_helper(root->right);
}

/**
 * Binary Tree Print Tree
 *
 * Parameters:
 * - Node* root: the root of the tree
 */
void bt_print(Node* root) {
    if (!root) {
        printf("Invalid tree.\n");
        return;
    }
    bt_print_helper(root);
    printf("\n");
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
