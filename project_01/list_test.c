#include "list.h"
#include <stdio.h>

int main(void) {
    // Create a new list
    list *myList = createlist();
    if (myList == NULL) { // check if NULL
        fprintf(stderr, "Error: Failed to create list.\n"); // if NULL print error
        return 1; // return error condition 1
    }

    // Add several strings to the list
    if (addtolist(myList, "First") != 0) { // looking for 0 to be returned so we know the the string was added to the list
        fprintf(stderr, "Error: Failed to add 'First' to list.\n"); // if not 0 then it didn't add and we have an error
    }
    if (addtolist(myList, "Second") != 0) { // same
        fprintf(stderr, "Error: Failed to add 'Second' to list.\n");
    }
    if (addtolist(myList, "Third") != 0) { // same
        fprintf(stderr, "Error: Failed to add 'Third' to list.\n");
    }

    // Print the list contents
    printf("List contents after additions:\n"); // after adding strings print out the contents
    printlist(myList);

    // Remove the head of the list and print the removed item
    char *removed = removefromlist(myList);
    if (removed != NULL) { // there is still something in the list
        printf("\nRemoved item: %s\n", removed); // what did we remove?  Print it out
        free(removed);  // free memory the string returned by removefromlist was using
    }
    else {
        printf("\nNo item removed; the list was empty.\n"); // if removed was NULL then the list was empty
    }

    // Print the list after removal
    printf("\nList contents after removal:\n");
    printlist(myList);

    // Flush the list
    flushlist(myList); // empty the list
    printf("\nList contents after flushing (should be empty):\n");
    printlist(myList); // if it is empty then nothing should be printed

    // Add new items after flushing
    if (addtolist(myList, "New First") != 0) { // again, looking for 0 to be returned so we know the list was added to
        fprintf(stderr, "Error: Failed to add 'New First' to list.\n");
    }
    if (addtolist(myList, "New Second") != 0) { // same
        fprintf(stderr, "Error: Failed to add 'New Second' to list.\n");
    }

    printf("\nList contents after adding new items:\n");
    printlist(myList);

    // Free the entire list
    freelist(&myList); // we are going to removed all nodes from the list and free up the memory they were using
    if (myList == NULL) { // check to make sure the list was destroyed
        printf("\nList successfully freed.\n");
    }
    else {
        printf("\nError: List not freed correctly.\n");
    }

    return 0;
}
