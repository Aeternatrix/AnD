#include <stdio.h>
#include <stdlib.h>

enum colour { RBT_RED, RBT_BLACK };

typedef struct Node {
    int data;
    enum colour colour;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

static Node* rbt_post_fix(Node* node);


/**
 * Red-Black Tree Create
 *
 * Creates a new Red-Black Tree Node
 * - Uses malloc()
 */
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

static Node*
rbt_right_rotate(Node* node) {
    Node* child = node->right;
    Node* parent = node->parent;
    Node* g_parent = parent->parent;
    
    if (g_parent) {
        if (parent == g_parent->left) {
            g_parent->left = node;
        } else g_parent->right = node;
    }
    node->parent = g_parent;

    parent->parent = node;
    node->right = parent;

    child->parent = parent;
    parent->left = child;

    return rbt_post_fix(parent);
}

/*
 * Red-Black Tree Insert
 *
 * Creates a new node and inserts it into the tree and then balances the tree
 */
Node* rbt_insert(Node* root, int data) {
    Node* node = rbt_create(data, RBT_RED);
    if (!root) {
        node->colour = RBT_BLACK;
        return node;
    }

    Node *parent, *current = root;
    
    while (current) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
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

static Node*
rbt_post_fix(Node* node) {
    Node* parent = node->parent;
    if (!parent) {
        node->colour = RBT_BLACK;
        return node;
    }

    if (parent->colour == RBT_BLACK) {
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

    if (parent->colour == RBT_RED && (uncle ? uncle->colour : RBT_BLACK) == RBT_RED) {
        parent->colour = RBT_BLACK;
        uncle->colour = RBT_BLACK;
        grand_parent->colour = RBT_RED;
        return rbt_post_fix(grand_parent);
    }

    if (parent->colour == RBT_RED && (uncle ? uncle->colour : RBT_BLACK) == RBT_BLACK) {
        if (p_left && !n_left) {
            return rbt_left_rotate(node);
        }
        if (p_left && n_left) {
            parent->colour = RBT_BLACK;
            grand_parent->colour = RBT_RED;
            return rbt_right_rotate(node->parent);
        }
        if (!p_left && n_left) {
            return rbt_right_rotate(node);
        }
        if (!p_left && !n_left) {
            parent->colour = RBT_BLACK;
            grand_parent->colour = RBT_RED;
            return rbt_left_rotate(node->parent);
        }
    }

    __builtin_unreachable();
}

/*
 * Red-Black Tree Print
 *
 * Prints the tree in order (smallest to largest)
 * - Uses printf()
 */
void
rbt_print(Node* root) {
    if (!root) return;

    rbt_print(root->left);
    printf("%s%d\033[0m ", root->colour == RBT_BLACK ? "\033[37m" : "\033[31m", root->data);
    rbt_print(root->right);
}


/*
 * Red-Black Tree Free
 *
 * Recursively frees the memory allocated with malloc
 * - Uses free()
 */
void rbt_free(Node* root) {
    if (!root) return;
    rbt_free(root->left);
    rbt_free(root->right);
    free(root);
}

/*
 * Red-Black Tree Search
 *
 * Recursively searches the tree for data
 * - Returns 1 if data is in the tree, 0 if not
 */
int
rbt_search(Node*root, int data) {
    if (root->data == data) return 1;
    if (data < root->data) return rbt_search(root->left, data);
    if (data >= root->data) return rbt_search(root->right, data);
    return 0;
}
