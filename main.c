#include "main.h"


/**
 * Create linked list and set it's head and tail to NULL
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
 */ 
int size(list_t *list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}

/**
 * Return whether or not the list is empty
 */
bool is_empty(list_t *list) {
    if (list == NULL) {
        return false;
    }
    return (list->size == 0);
}

/**
 * Return the position of the first element (NULL if empty)
 */ 
node_t *first(list_t *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}

/**
 * Return the position of the last element (NULL if empty)
 */ 
node_t *last(list_t *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->tail;
}

/**
 * Return the position immediately before p (NULL if p is first)
 */
node_t *before(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || p == list->head) {
        return NULL;
    }
    node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node->next == p) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

/**
 * Return the position immediately after p (NULL if p is last)
 */
node_t *after(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || p == list->tail) {
        return NULL;
    }
    return p->next;
}

/**
 * Create new node with element e and set it as the head of the list. Return 
 * the position of the element
 */
node_t *insert_first(list_t *list, void *e) {
     if (list == NULL) {
        return NULL;
    }
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    if (list->size == 1) {
        list->tail = list->head;
    }
    return new_node;
}

/**
 * Insert e in front of the element at position p. Return the position
 * of the element. Note you cannot use this if the list is empty
 */
node_t *insert_before(list_t *list, node_t *p, void *e) {
    if (list == NULL || p == NULL) {
        return NULL;
    }

    // Insert before the current head
    if (list->head == p) {
        return insert_first(list, e);
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
        return NULL;
    }

    // Create node, set its element to e, and add it before prev_node (and before p)
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = p;
    prev_node->next = new_node;
    list->size++;
    return new_node;
}

/**
 * Create new node with element e and set it as the tail of the list. Return
 * the position of the element
 */
node_t *insert_last(list_t *list, void *e) {
     if (list == NULL) {
        return NULL;
    }
    if (list->size == 0) {
        return insert_first(list, e);
    }
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = NULL;
    list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
    return new_node;
}

/**
 * Insert e following the element at position p. Return the 
 * position of the element. Note you cannot use this if the list is empty
 */
node_t *insert_after(list_t *list, node_t *p, void *e) {
    if (list == NULL || p == NULL) {
        return NULL;
    }

    // Insert after the current tail
    if (list->tail == p) {
        return insert_last(list, e);
    }

    // Find the previous node (p)
    node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node == p) { // Previous node has been found
            break;
        }
        current_node = current_node->next;
    }

    if (current_node == NULL) { // Either list is empty or p was not found
        return NULL;
    }

    // Create node, set its element to e, and add it after current_node 
    node_t *new_node = malloc(sizeof(node_t));
    new_node->element = e;
    new_node->next = current_node->next;
    current_node->next = new_node;
    list->size++;
    return new_node;
}

/**
 * Remove list->head and return its element. Return NULL if empty
 */
void *remove_first(list_t *list) {
    if (list == NULL || list->head == NULL) {
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
 */
void *remove_last(list_t *list) {
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }

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
        return NULL;
    }

    // Remove the tail
    node_t *rem_node = list->tail;
    void *rem_element = rem_node->element;
    list->tail = current_node;
    list->tail->next = NULL;
    free(rem_node);
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return rem_element;
}

/**
 * Remove and return the element at position p
 */
void *remove_node(list_t *list, node_t *p) {
    if (list == NULL || p == NULL || list->size == 0) {
        return NULL;
    }

    if (list->head == p) {
        return remove_first(list);
    }

    if (list->tail == p) {
        return remove_last(list);
    }

    // Find p and it's previous node
    node_t *prev_node = list->head;
    node_t *current_node = list->head->next;
    while (current_node != NULL) {
        if (current_node == p) {
            break;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (current_node == NULL) {
        return NULL; // Either list->head->next is NULL or p was not found
    }

    // Remove current_node (p)
    void *rem_element = current_node->element;
    prev_node->next = current_node->next;
    free(current_node);
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return rem_element;
}

/**
 * Free all memory associated with the list
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