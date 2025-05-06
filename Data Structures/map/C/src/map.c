#include <stdlib.h>

enum map_colour { MAP_BLACK, MAP_RED };
typedef unsigned long uint64;

/*
 * Node for a generic map in C.
 *
 * Key is a base37 value made from a string up to 12 characters long.
 *
 * Data is a void pointer and must be allocated yourself.
 *
 * map_free() will take a function for a function to free the allocated data memory.
 */
typedef struct Node {
    uint64 key;
    void* data;
    enum map_colour colour;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

static Node* map_post_fix(Node* node);

static uint64
map_key_convert_stol(char* str) {
    char c = str[0];
    int itr = 0;
    uint64 rt = 0;
    for (; c != '\0' && itr != 12; itr++) {
        c = str[itr];
        if (c >= 'a' && c <= 'z') {
            rt *= 37;
            rt += c - 'a' + 11;
        } else if (c >= 'A' && c <= 'Z') {
            rt *= 37;
            rt += c - 'A' + 11;
        } else if (c >= '0' && c <= '9') {
            rt *= 37;
            rt += c - '0' + 1;
        } else if (c == '_') {
            rt *= 37;
        }
    }
    return rt;
}

static void
map_key_convert_ltos(uint64 key, char* out) {
    uint64 tkey = key;
    int itr = 0;
    while (tkey != 0 && itr != 12) {
        int c = tkey % 37;
        if (c == 0) {
            out[itr++] = '_';
        } else if (c >= 1 && c <= 10) {
            tkey -= c;
            out[itr++] = c - 1 + '0';
        } else if (c >= 11 && c <= 36) {
            tkey -= c;
            out[itr++] = c - 11 + 'a';
        }
        tkey /=37;
    }
    char* st = out;
    char* en = out + itr -1;

    while (st < en) {
        char tmp = *st;
        *st++ = *en;
        *en-- = tmp;
    }
}

/*
 * Map Create
 *
 * Creates a new Map with a Key-Value-Pair. Key can be alphanumeric and '_' other characters are ignored. Key can only be up to 12 characters long.
 * - Key is alphbetical a la _0123456789abcdefghijklmnopqrstuvwxyz
 * - Uses malloc()
 */
Node*
map_create(char* key, void* data, enum map_colour colour) {
    Node* node = malloc(sizeof(Node));
    node->key = map_key_convert_stol(key);
    node->data = data;
    node->colour = colour;
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    return node;
}

static Node*
map_root(Node* node) {
    Node* rt = node;
    while (rt->parent) rt = rt->parent;
    return rt;
}

static Node*
map_left_rotate(Node* node) {
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

    if (child) child->parent = parent;
    parent->right = child;

    return map_post_fix(parent);
}

static Node*
map_right_rotate(Node* node) {
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

    if (child) child->parent = parent;
    parent->left = child;

    return map_post_fix(parent);
}

/* 
 * Map Insert
 *
 * Creates a new kvp and inserts it into the tree; then balances the tree
 * - Expects a function of signature void fn(void*) to deal with collisions (updating kvp)
 * - Returns the tree root
 */
Node*
map_insert(Node* root, char* key, void* data, void (*free_fn)(void*)) {
    Node* node = map_create(key, data, MAP_RED);
    if (!root) {
        node->colour = MAP_BLACK;
        return node;
    }
    Node *parent, *current = root;

    while (current) {
        parent = current;
        if (node->key < current->key) {
            current = current->left;
        } else if (node->key > current->key) {
            current = current->right;
        } else {
            //-- Key found
            break;
        }
    }

    if (current) { //-- Key in tree
        free_fn(current->data);
        current->data = data;
        return root;
    }

    node->parent = parent;
    if (node->key < parent->key) parent->left = node;
    else parent->right = node;

    if (!parent->parent) return root;

    return map_post_fix(node);
}

static Node*
map_post_fix(Node* node) {
    Node* parent = node->parent;
    if (!parent) {
        node->colour = MAP_BLACK;
        return node;
    }

    if (parent->colour == MAP_BLACK) {
        return map_root(node);
    }

    Node* grand_parent = parent->parent;
    if (!grand_parent) return parent;

    int p_left = grand_parent->left == parent,
        n_left = parent->left == node;
    Node* aunt;

    if (p_left) aunt = grand_parent->right;
    else aunt = grand_parent->left;

    if (parent->colour == MAP_RED && (aunt ? aunt->colour : MAP_BLACK) == MAP_RED) {
        parent->colour = MAP_BLACK;
        aunt->colour = MAP_BLACK;
        grand_parent->colour = MAP_RED;
        return map_post_fix(grand_parent);
    }

    if (parent->colour == MAP_RED && (aunt ? aunt->colour : MAP_BLACK) == MAP_BLACK) {
        if (p_left && !n_left) return map_left_rotate(node);
        if (p_left && n_left) {
            parent->colour = MAP_BLACK;
            grand_parent->colour = MAP_RED;
            return map_right_rotate(node->parent);
        }

        if (!p_left && n_left) return map_right_rotate(node);
        if (!p_left && !n_left) {
            parent->colour = MAP_BLACK;
            grand_parent->colour = MAP_RED;
            return map_left_rotate(node->parent);
        }
    }

    __builtin_unreachable();
}

/*
 * Map Print
 *
 * Prints the data in key-based-alphabetical order according to your print function
 * - Alphabetical order being _0123456789abcdefghijklmnopqrstuvwxyz
 * - expects a function of signature void fn(char*, Node*) where char* is the key value as a string
 */
void
map_print(Node* root, void (*print_fn)(char*, Node*)) {
    if (!root) return;

    map_print(root->left, print_fn);
    char key[13] = {};
    map_key_convert_ltos(root->key, key);
    print_fn(key, root);
    map_print(root->right, print_fn);
}

/*
 * Map Free
 *
 * Recursively frees the memory allocated with malloc
 * - Pass a function of signature void fn(void*) to free the allocated data
 */
void
map_free(Node* root, void (*free_fn)(void*)) {
    if (!root) return;
    map_free(root->left, free_fn);
    map_free(root->right, free_fn);
    free_fn(root->data);
    free(root);
}

static void*
map_search_internal(Node* root, uint64 key) {
    if (root->key == key) return root->data;
    if (key < root->key) return map_search_internal(root->left, key);
    if (key > root->key) return map_search_internal(root->right, key);
    return 0;
}

/*
 * Map Search Value By Key
 *
 * Recursively Searches the Tree for the key of a kvp
 * - Returns value (void*) of the kvp if found, 0 if not
 */
void*
map_search(Node* root, char* key) {
    uint64 ckey = map_key_convert_stol(key);
    return map_search_internal(root, ckey);
}
