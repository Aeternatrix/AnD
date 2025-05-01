#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

/**
 * Binary Search Tree Create
 *
 * Parameters:
 * - int data: the data to be inserted as root
 * 
 * Returns:
 * - Node*: a reference to the created Node
 */
Node* bst_create(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->left = 0;
    node->right = 0;

    return node;
}

/**
 * Binary Search Tree Insert
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - int data: the data to insert
 *
 * Return:
 * - int: 0 on success, -1 on failure
 */
int bst_insert(Node* root, int data) {
    if (!root) return -1;

    if (data < root->data) {
        if (root->left) bst_insert(root->left, data);
        else {
            root->left = bst_create(data);
            return 0;
        }
    } else if (data > root->data) {
        if (root->right) bst_insert(root->right, data);
        else {
            root->right = bst_create(data);
            return 0;
        }
    }
    
    return -1;
}

/**
 * Binary Search Tree Search
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - int data: the data to find
 * 
 * Returns:
 * - Node*: the node of the found data; 0 on failure
 */
Node* bst_search(Node* root, int data) {
    if (!root) return 0;

    if (data < root->data) {
        if (root->left) return bst_search(root->left, data);
        else {
            return 0;
        }
    } else if (data > root->data) {
        if (root->right) return bst_search(root->right, data);
        else {
            return 0;
        }
    } else if (data == root->data) {
        return root;
    }
    
    return 0;
}

/**
 * Binary Search Tree Minimum Value
 *
 * Parameters:
 * - Node* root: the root of the tree
 * 
 * Returns:
 * - Node*: the node of the found data; 0 on failure
 */
Node* bst_min(Node* root) {
    Node* current = root;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

/**
 * Binary Search Tree Maximal Value
 *
 * Parameters:
 * - Node* root: the root of the tree
 * 
 * Returns:
 * - Node*: the node of the found data; 0 on failure
 */
Node* bst_max(Node* root) {
    Node* current = root;
    while (current->right) {
        current = current->right;
    }
    return current;
}

/**
 * Binary Search Tree Delete
 *
 * Parameters:
 * - Node* root: the root of the tree
 * - int data: the data to delete
 * 
 * Returns:
 * - Node*: the root node of the tree
 */
Node* bst_delete(Node* root, int data) {
    if (!root) return root;

    if (root->data > data) {
        bst_delete(root->left, data);
    } else if (root->data < data) {
        bst_delete(root->right, data);
    } else {
        if (!root->left) {
            Node* replacement = root->right;
            free(root);
            return replacement;
        }
        if (!root->right) {
            Node* replacement = root->left;
            free(root);
            return replacement;
        }

        Node* replacement = bst_min(root->right);
        root->data = replacement->data;
        root->right = bst_delete(root->right, replacement->data);
    }
    return root;
}

static
void bst_print_helper(Node* root) {
    if (!root) return;

    bst_print_helper(root->left);
    printf("%d ", root->data);
    bst_print_helper(root->right);
}

/**
 * Binary Tree Print Tree
 *
 * Parameters:
 * - Node* root: the root of the tree
 */
void bst_print(Node* root) {
    if (!root) {
        printf("Invalid tree.\n");
        return;
    }
    bst_print_helper(root);
    printf("\n");
}

/**
 * Binary Search Tree Free Tree Memory
 *
 * Parameters:
 * - Node* root: the root of the tree
 */
void bst_free(Node* root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
