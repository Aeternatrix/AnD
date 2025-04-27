#include <stdio.h> // printf
#include <stdlib.h> // malloc

typedef struct Node {
    int data;
    struct Node* next;
} Node;


/**
 * Singly Linked List Create
 *
 * Parameters:
 * - int data: the data to be inserted
 *
 * Returns:
 * - Node*: a reference to the created node
 */
Node* sll_create(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = 0;

    return node;
}

/**
 * Singly Linked List Insert
 *
 * Parameters:
 * - Node* head: the head of the linked list
 * - int data: the data to be inserted
 * - int pos: the position to insert into
 *
 * Returns:
 * - int: 0 on failure, Node* on success
 */
Node* sll_insert(Node* head, int data, int pos) {
    if (!head) return 0; //-- head doesn't exist; early return

    Node* current = head;

    if (pos == 0) {
        Node* node = sll_create(data);
        node->next = head;
        return node;
    }

    for (int itr=0; itr < pos; itr++) {
        current = current->next;
        if (!current) return 0; //-- position not in list
    }

    Node* node = sll_create(data);
    
    node->next = current->next;
    current->next = node;
    
    return head;
}

/**
 * Singly Linked List Append Data
 *
 * Parameters:
 * - Node* head: the head of the linked list
 * - Node* node: the node to be appended
 *
 * Returns:
 * - int: 0 on failure, 1 on success
 */
int sll_append_node(Node* head, Node* node) {
    if (!head || !node) return 0; //-- head or node doesn't exist; early return

    Node* current = head;
    
    for (;;) {
        if (!current->next) break;
        current = current->next;
    }

    current->next = node;

    return 1;
}

/**
 * Singly Linked List Append Data
 *
 * Parameters:
 * - Node* head: the head of the linked list
 * - int data: the data to be inserted
 *
 * Returns:
 * - int: 0 on failure, 1 on success
 */
int sll_append_data(Node* head, int data) {
    if (!head) return 0; //-- head doesn't exist; early return

    Node* node = sll_create(data);
    return sll_append_node(head, node);
}

/**
 * Singly Linked List Get Node
 *
 * Parameters:
 * - Node* head: the head of the linked list
 * - int pos: the position of the node to retrive
 *
 * Returns:
 * - int: 0 on failure, Node* on success
 */
Node* sll_get_node(Node* head, int pos) {
    if (!head) return 0;

    Node* current = head;
    for (int itr=0; itr < pos; itr++) {
        current = current->next;
        if (!current) return 0; //-- position not in list
    }

    return current;
}

/**
 * Singly Linked List Delete Node
 * 
 * Parameters:
 * - Node* head: the head of the linked list
 * - int pos: the position of the node to retrive
 *
 * Returns:
 * - int: 0 on failure, Node* head on success
 */
Node* sll_delete_node(Node* head, int pos) {
    if (!head) return 0;

    Node* current = head->next;
    Node* prev = head;

    if (pos == 0) {
        free(head);
        return current;
    }

    for (int itr=0; itr < pos; itr++) {
        prev = current;
        current = current->next;
        if (!current) return 0; //-- position not in list
    }
    
    prev->next = current->next;

    free(current);

    return head;
}

/**
 * Singly Linked List Free List
 *
 * Parameters:
 * - Node* head: the head of the linked list
 */
void sll_free(Node* head) {
    Node* tmp = head;
    Node* current = head->next;
    while (current) {
        free(tmp);
        tmp = current;
        current = current->next;
    }
    free(tmp);
}

/**
 * Singly Linked List Print List
 *
 * Parameters:
 * - Node* head: the head of the linked list
 */
void sll_print(Node* head) {
    if (!head) return; //-- head or node doesn't exist; early return

    Node* current = head;
    for (;;) {
        printf("%d ", current->data);
        if (!current->next) break;
        current = current->next;
    }
    printf("\n");
}
