#include "list.h"

/* Most of the way I did this code comes from Deb Hardings class for C
CS 2060.  I adapted the linked list code that we used in our final CS2060 
assignment to this Project 1 */


// Creates a new list, allocates memory, and initializes head to NULL
list *createlist(void) {
    list *new_list = (list *)malloc(sizeof(list)); // allocate memory to the node we are adding to the list
    if (new_list == NULL) { // checking if the new list has nothing in it
        return NULL;
    }
    new_list->head = NULL; // if not NULL then update the head location, the head will have a NULL
    return new_list;
}

// Adds a new node containing the string item to the end of the list
int addtolist(list *ll, char *item) {
    if (ll == NULL || item == NULL) { // we have an error condition here
        return -1;
    }

    // Allocate a new node
    node *new_node = (node *)malloc(sizeof(node)); // allocate memory
    if (new_node == NULL) { // check for error condition
        return -1;
    }

    /* Allocate memory for the string copy.
       Using strdup here for brevity; if not available, use malloc, strlen, and strncpy. */
    new_node->item = strdup(item); // add the string to the node
    if (new_node->item == NULL) {
        free(new_node); // free up memory used by node
        return -1; // return error code
    }
    new_node->next = NULL; // update the head of the list

    // Insert node at the end of the list
    if (ll->head == NULL) {
        ll->head = new_node;
    }
    else { // moving where the head of the list is
        node *current = ll->head; // by looking at the node
        while (current->next != NULL) { // checking if it is NULL
            current = current->next; // and then moving to the next node
        }
        current->next = new_node;
    }
    return 0;
}

// Removes the head node from the list, returns its stored string
char *removefromlist(list *ll) {
    if (ll == NULL || ll->head == NULL) { // we are at the head of the list, or list is empty
        return NULL;
    }

    node *temp = ll->head; // get the location of the head of the list
    char *item_str = temp->item;  // save the string pointer
    ll->head = temp->next;        // move head to the next node
    free(temp);                   // free the removed node
    return item_str;
}

// Prints every string stored in the list nodes
void printlist(list *ll) {
    if (ll == NULL) {
        return;
    }

    node *current = ll->head;
    while (current != NULL) { // loop through nodes
        printf("%s\n", current->item); // print the string contents
        current = current->next; // save current position so we can move to the next node
    }
}

/* Flushes (clears) the list by freeing all nodes and their strings.
   The list structure remains allocated and its head is set to NULL. */
void flushlist(list *ll) {
    if (ll == NULL) { // list is empty
        return;
    }

    node *current = ll->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp->item); // delete string
        free(temp); // delete node
    }
    ll->head = NULL; // move the head
}

// Frees the entire list, including all nodes, their strings, and the list structure itself
void freelist(list **ll) {
    if (ll == NULL || *ll == NULL) {
        return;
    }

    flushlist(*ll); // destroy the hlist
    free(*ll); // free the memory of each node in the list
    *ll = NULL; // set list to be empty
}
