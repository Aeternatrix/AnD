#include <stdio.h>
#include <stdlib.h>

enum colour { NONE, RED, BLACK };

typedef struct Node {
    int data;
    enum colour colour;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

static Node* rbt_post_fix(Node* node);

Node* rbt_create(int data, enum colour colour) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->colour = colour;
    node->parent = 0;
    node->left = 0;
    node->right = 0;

    return node;
}

static Node*
rbt_root(Node* node) {
    Node* rt = node;
    while(rt->parent) {
        rt = rt->parent;
    }
    return rt;
}

// The goal is to get this
//
//   parent
//      \
//       \
//      node
//     /     \
//    /       \
//  child1   child2
//
// To look like this
//
//      node
//      /   \
//     /     \
//  parent  child2
//    \
//     \
//    child1
static Node*
rbt_left_rotate(Node* node) {
    Node* child = node->left;
    Node* parent = node->parent;
    Node* g_parent = parent->parent;
    
    if (g_parent) {
        if (parent == g_parent->left) {
            g_parent->left = node;
        } else g_parent->right = node;
    }
    node->parent = g_parent;

    parent->parent = node;
    node->left = parent;

    child->parent = parent;
    parent->right = child;

    return rbt_post_fix(parent);
}

// mirror of the above
static Node*
rbt_right_rotate(Node* node) {
    Node* child = node->right;
    Node* parent = node->parent;
    Node* g_parent = parent->parent;
    
    node->parent = parent->parent;
    node->right = parent;
    parent->parent = node;
    if (g_parent) {
        if (parent == g_parent->right) {
            g_parent->right = node;
        } else g_parent->left = node;
    }

    parent->left = child;
    child->parent = parent;

    return rbt_post_fix(parent);
}

Node* rbt_insert(Node* root, int data) {
    Node* node = rbt_create(data, RED);
    if (!root) {
        node->colour = BLACK;
        return node;
    }

    Node *parent, *current = root;
    
    while (current) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            //-- Overwrite other stuff™ in this node
            //-- Not implemented in this version
            //-- This branch is just a copy of data > current->data
            current = current->right;
        }
    }
    node->parent = parent;
    if (data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    if (!node->parent->parent) {
        return root;
    }
    return rbt_post_fix(node);
}

// The goal is to make it so that the rb tree doesn't break any requirements
// 
static Node*
rbt_post_fix(Node* node) {
    Node* parent = node->parent;
    if (!parent) {
        node->colour = BLACK;
        return node;
    }

    if (parent->colour == BLACK) {
        return rbt_root(node);
    }

    //-- check uncle
    Node* grand_parent = parent->parent;
    if (!grand_parent) {
        return parent;
    }

    int p_left = grand_parent->left == parent,
        n_left = parent->left == node;
    Node* uncle;
    if (p_left) {
        uncle = grand_parent->right;
    } else {
        uncle = grand_parent->left;
    }

    //-- Case 1: Uncle and Parent are RED
    //-- Invert the colour of the Uncle, Parent, and Grandparent
    //-- Recurse on the Grandparent

    if (parent->colour == RED && uncle->colour == RED) {
        parent->colour = BLACK;
        uncle->colour = BLACK;
        grand_parent->colour = RED;
        return rbt_post_fix(grand_parent);
    }

    //-- Case 2: Uncle is BLACK and Parent is RED
    //-- Rotate to align

    if (parent->colour == RED && uncle->colour == BLACK) {
        if (p_left && !n_left) {
            return rbt_left_rotate(node);
        }
        if (p_left && n_left) {
            parent->colour = BLACK;
            grand_parent->colour = RED;
            return rbt_right_rotate(node->parent);
        }
        if (!p_left && n_left) {
            return rbt_left_rotate(node);
        }
        parent->colour = BLACK;
        grand_parent->colour = RED;
        return rbt_right_rotate(node->parent);
    }

    __builtin_unreachable();
}

void
rbt_print(Node* root) {
    if (!root) return;

    rbt_print(root->left);
    printf("%s%d\033[0m ", root->colour == BLACK ? "\033[37m" : "\033[31m", root->data);
    rbt_print(root->right);
}

void rbt_free(Node* root) {
    if (!root) return;
    rbt_free(root->left);
    rbt_free(root->right);
    free(root);
}
