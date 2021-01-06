#include "main.h"


/**
 * Create linked list and set it's head and tail to NULL and size to 0
 * Time Complexity: O(1)
 */
list_t *create_list() {
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * Return the number of elements stored
 * Time Complexity: O(1)
 */ 
int size(list_t *list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return 0;
    }
    return list->size;
}

/**
 * Return whether or not the list is empty
 * Time Complexity: O(1)
 */
bool is_empty(list_t *list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return true;
    }
    return (list->size == 0);
}

/**
 * Find and return the node containing element e. Return NULL if it's not found
 * Time Complexity: O(n)
 */
node_t *get_node(list_t *list, void *e) {
    if (list == NULL) {
        printf("List is NULL\n");
        return NULL;
    }

    // Find and return the node with element e
    node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node->element == e) {
            return current_node;
        }
        current_node = current_node->next;
    }

    // Not found
    printf("The node was not found in the list\n");
    return NULL;
}

/**
 * Return the position of the first element (NULL if empty)
 * Time Complexity: O(1)
 */ 
node_t *first(list_t *list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return NULL;
    }
    return list->head;
}

/**
 * Return the position of the last element (NULL if empty)
 * Time Complexity: O(1)
 */ 
node_t *last(list_t *list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return NULL;
    }
    return list->tail;
}

/**
 * Return the position immediately before p (NULL if p is first)
 * Time Complexity: O(n)
 */
node_t *before(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || p == list->head) {
        printf("List is NULL or p is NULL or p is list->head\n");
        return NULL;
    }
    node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node->next == p) {
            return current_node;
        }
        current_node = current_node->next;
    }
    printf("Node before was not found\n");
    return NULL;
}

/**
 * Return the position immediately after p (NULL if p is last)
 * Time Complexity: O(1)
 */
node_t *after(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || p == list->tail) {
        printf("List is NULL or p is NULL or p is list->tail\n");
        return NULL;
    }
    return p->next;
}

/**
 * Create new node with element e and set it as the head of the list. Return 
 * the position of the element
 * Time Complexity: O(1)
 */
void insert_first(list_t *list, void *e) {
     if (list == NULL) {
        printf("List is NULL\n");
        return;
    }
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    if (list->size == 1) {
        list->tail = list->head;
    }
}

/**
 * Insert e in front of the element at position p. Return the position
 * of the element. 
 * Time Complexity: O(n)
 */
void insert_before(list_t *list, node_t *p, void *e) {
    if (list == NULL || p == NULL) {
        printf("List is NULL or p is NULL\n");
        return;
    }

    // Insert before the current head
    if (list->head == p) {
        insert_first(list, e);
        return;
    }

    // Find the previous node
    node_t *prev_node = list->head;
    while (prev_node != NULL) {
        if (prev_node->next == p) { // Previous node has been found
            break;
        }
        prev_node = prev_node->next;
    }

    if (prev_node == NULL) { // Either list is empty or p was not found
        printf("List is empty or p was not found in the list\n");
        return;
    }

    // Create node, set its element to e, and add it before prev_node 
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = p;
    prev_node->next = new_node;
    list->size++;
}

/**
 * Create new node with element e and set it as the tail of the list. Return
 * the position of the element
 * Time Complexity: O(1)
 */
void insert_last(list_t *list, void *e) {
     if (list == NULL) {
        return;
    }
    if (list->size == 0) {
        insert_first(list, e);
        return;
    }
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = NULL;
    list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
}

/**
 * Insert e following the element at position p. Return the 
 * position of the element. 
 * Time Complexity: O(1)
 */
void insert_after(list_t *list, node_t *p, void *e) {
    if (list == NULL || p == NULL) {
        printf("List is NULL or p is NULL\n");
        return;
    }

    // Insert after the current tail
    if (list->tail == p) {
        insert_last(list, e);
        return;
    }

    // Create node, set its element to e, and add it after p
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = p->next;
    p->next = new_node;
    list->size++;
}

/**
 * Remove list->head and return its element. Return NULL if empty
 * Time Complexity: O(1)
 */
void *remove_first(list_t *list) {
    if (list == NULL || list->head == NULL) {
        printf("List is NULL or list->head is NULL (list is empty)\n");
        return NULL;
    }

    // Remove the head
    node_t *rem_node = list->head;
    void *rem_element = rem_node->element;
    list->head = list->head->next;
    free(rem_node);
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return rem_element;
}

/**
 * Remove list->tail and return its element. Return NULL if empty
 * Time Complexity: O(n)
 */
void *remove_last(list_t *list) {
    if (list == NULL || list->tail == NULL) {
        printf("List is NULL or list->tail is NULL (list is empty)\n");
        return NULL;
    }

    // If there is only one element in the list
    if (list->head == list->tail) {
        return remove_first(list);
    }

    // Find the new tail
    node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node->next == list->tail) { // New tail has been found
            break;
        }
        current_node = current_node->next;
    }

    if (current_node == NULL) { // Either list is empty or new tail was not found
        printf("List is empty or new tail was not found\n");
        return NULL;
    }

    // Remove the tail
    node_t *rem_node = list->tail;
    void *rem_element = rem_node->element;
    list->tail = current_node;
    list->tail->next = NULL;
    free(rem_node);
    list->size--;
    return rem_element;
}

/**
 * Remove and return the element at position p
 * Time Complexity: O(n)
 */
void *remove_node(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || list->size == 0) {
        printf("List is NULL or p is NULL or list is empty\n");
        return NULL;
    }

    if (list->head == p) {
        return remove_first(list);
    }

    if (list->tail == p) {
        return remove_last(list);
    }

    // Find p's previous node
    node_t *prev_node = list->head;
    while (prev_node != NULL) {
        if (prev_node->next == p) {
            break;
        }
        prev_node = prev_node->next;;
    }

    if (prev_node == NULL) {
        printf("Previous node was node found\n");
        return NULL; // There is no previous node
    }

    // Remove p
    void *rem_element = p->element;
    prev_node->next = p->next;
    free(p);
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return rem_element;
}

/**
 * Free all memory associated with the list
 * Time Complexity: O(n)
 */
void destroy_list(list_t *list) {
    node_t *next_node = NULL;
    node_t *current_node = list->head;
    while (current_node != NULL) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
}