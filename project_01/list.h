#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Some assumptions I made here.

ll is short for linked list
The node is just a block in the list
the List is the list that the nodes will be linked in
char in the node is some string or character

*/

/* Declare all the structs as specified */
typedef struct Node node;

struct Node {
    char *item;
    node *next;
};

typedef struct List {
    node *head;
} list;

/* 
 * Allocates space for a new list and sets its head to NULL.
 * Returns the created list if successful, NULL otherwise.
 */
list *createlist(void);

/* 
 * Allocates a new node and copies the string from item to this node
 * (using malloc, strlen, and strncpy or strdup). Adds this new node
 * to the end of the list ll. Returns 0 if successful, non-zero otherwise.
 */
int addtolist(list *ll, char *item);

/* 
 * Removes the head of the list ll (and moves the head of ll to the next node
 * in the list), extracts the string stored in the head, and returns a pointer
 * to this string. Also frees the removed head node.
 */
char *removefromlist(list *ll);

/* 
 * Prints every string in each node of the list ll, with a new line
 * character at the end of each string.
 */
void printlist(list *ll);

/* 
 * Flushes (clears) the entire list and re-initializes the list. The passed
 * pointer ll should still point to a valid, empty list when this function
 * returns. Any memory allocated to store nodes in the list should be freed.
 */
void flushlist(list *ll);

/* 
 * De-allocates all data for the list. Ensures all memory allocated for list
 * ll is freed, including any allocated strings and the list ll itself.
 * The input is a pointer to the list pointer (list **ll) so that after freeing,
 * the original pointer can be set to NULL.
 */
void freelist(list **ll);

#endif /* LIST_H */
