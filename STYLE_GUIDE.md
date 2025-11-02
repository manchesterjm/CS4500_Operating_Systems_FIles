# C/C Style Guide

**CS4500 Operating Systems - Coding Standards**

**Version**: 1.0
**Last Updated**: November 2, 2025
**Project**: CS4500 Operating Systems Course

This document defines the coding standards for all C code in this project. All contributors must follow these guidelines to ensure consistency, maintainability, and code quality.

---

## Table of Contents

1. [General Principles](#general-principles)
2. [File Naming Conventions](#file-naming-conventions)
3. [C Style Conventions](#c-style-conventions)
4. [Naming Conventions](#naming-conventions)
5. [Code Organization](#code-organization)
6. [Functions](#functions)
7. [Documentation](#documentation)
8. [Error Handling](#error-handling)
9. [Header Files](#header-files)
10. [Memory Management](#memory-management)
11. [Kernel Module Specifics](#kernel-module-specifics)
12. [Makefiles](#makefiles)
13. [Code Review Checklist](#code-review-checklist)

---

## General Principles

### Core Values
1. **Readability First**: Code is read more often than written
2. **Explicit is Better Than Implicit**: Clear over clever
3. **Consistency**: Follow existing patterns in the codebase
4. **DRY (Don't Repeat Yourself)**: Extract common functionality
5. **YAGNI (You Aren't Gonna Need It)**: Don't build for hypothetical futures
6. **Safety**: Always check return values and validate inputs

### Code Quality Standards
- **Memory Safety**: No memory leaks (verify with valgrind)
- **Compilation**: Zero warnings with `-Wall -Wextra`
- **Formatting**: Consistent indentation and spacing
- **Documentation**: All functions must have comment blocks
- **Testing**: Test all functions with representative inputs

---

## File Naming Conventions

### Source Files
```
# C source files: lowercase with underscores
list.c              # GOOD
list_test.c         # GOOD
print_other.c       # GOOD

List.c              # BAD - don't use capital letters
listTest.c          # BAD - don't use camelCase
```

### Header Files
```
# Header files: lowercase with underscores, .h extension
list.h              # GOOD
print_other.h       # GOOD

List.h              # BAD
list.H              # BAD
```

### Documentation Files
```
# Documentation: All caps README with extension
README.txt          # GOOD
README.md           # GOOD

ReadMe.txt          # BAD - inconsistent capitalization
readme.txt          # BAD - should be all caps
```

### Makefiles
```
# Makefiles: Capital M, no extension
Makefile            # GOOD - standard convention

makefile            # ACCEPTABLE - works but less standard
GNUmakefile         # ACCEPTABLE - GNU-specific
```

---

## C Style Conventions

### Line Length
```c
/* Maximum line length: 100 characters
 * This balances readability with modern display sizes */

// BAD: Line too long
printf("This is an extremely long message that goes on and on and really should be broken up into multiple lines for readability\n");

// GOOD: Line broken appropriately
printf("This is a long message that has been broken into "
       "multiple lines for better readability\n");
```

### Indentation
```c
/* Use 4 spaces per indentation level (never tabs)
 * Exception: Kernel modules use tabs per Linux kernel style */

// GOOD
void calculate_total(int *items, int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (items[i] > 0) {
            total += items[i];
        }
    }
    return total;
}
```

### Braces
```c
/* Opening brace on same line for functions (K&R style)
 * Exception: Kernel modules follow Linux kernel style (brace on next line) */

// GOOD - User-space C (K&R style)
void my_function(void) {
    if (condition) {
        do_something();
    } else {
        do_something_else();
    }
}

// GOOD - Kernel module style
static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0;
}
```

### Whitespace
```c
// GOOD - space after keywords, before braces
if (x == 4) {
    printf("%d\n", x);
}

// BAD - missing spaces
if(x==4){
    printf("%d\n",x);
}

// GOOD - no space between function name and parenthesis
my_function(arg1, arg2);

// BAD - space between function and parenthesis
my_function (arg1, arg2);

// GOOD - spaces around operators
x = a + b * c;

// BAD - no spaces
x=a+b*c;
```

### Blank Lines
```c
/* Two blank lines between function definitions */
void first_function(void) {
    // Implementation
}


void second_function(void) {
    // Implementation
}


/* Use blank lines to separate logical sections within functions */
void complex_function(void) {
    // Setup
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) {
        return;
    }

    // Processing
    for (int i = 0; i < 100; i++) {
        data[i] = process(i);
    }

    // Cleanup
    free(data);
}
```

---

## Naming Conventions

### General Rules
```c
/* Variables and functions: lowercase_with_underscores */
int user_count = 10;
char *get_user_name(void);

/* Struct types: lowercase_with_underscores or CapitalizedWords */
struct node {
    int data;
    struct node *next;
};

typedef struct Node {
    int data;
    struct Node *next;
} node;

/* Constants and macros: UPPERCASE_WITH_UNDERSCORES */
#define MAX_BUFFER_SIZE 1024
#define DEFAULT_TIMEOUT 300

/* Enums: UPPERCASE_WITH_UNDERSCORES for values */
enum status {
    STATUS_SUCCESS,
    STATUS_ERROR,
    STATUS_PENDING
};
```

### Function Names
```c
/* Use verb_noun pattern for functions */
void create_list(void);          // GOOD
void list_create(void);           // ALSO GOOD
int add_to_list(list *ll);        // GOOD

void list(void);                  // BAD - not descriptive
void func1(void);                 // BAD - meaningless name
```

### Boolean Variables
```c
/* Use is_, has_, can_, should_ prefixes for boolean-like variables */
int is_empty = 1;
int has_data = 0;
int can_proceed = 1;

/* BAD - ambiguous */
int empty = 1;        // Does 1 mean empty or not empty?
int data = 0;         // Is this a boolean or data value?
```

### Pointer Naming
```c
/* Pointer notation: attach * to variable name, not type */
int *ptr;             // GOOD
int* ptr;             // LESS CLEAR - looks like type is "int*"

/* Multiple declarations */
int *ptr1, *ptr2;     // CLEAR
int* ptr1, ptr2;      // CONFUSING - ptr2 is not a pointer!
```

---

## Code Organization

### File Organization
```c
/*
 * list.c - Linked list implementation
 *
 * This module provides a linked list data structure for storing
 * dynamically allocated strings.
 */

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local includes */
#include "list.h"

/* Constants */
#define MAX_STRING_LENGTH 256

/* Static (file-local) function declarations */
static void internal_helper(void);

/* Public function implementations */
list *createlist(void) {
    /* Implementation */
}

/* Static function implementations */
static void internal_helper(void) {
    /* Implementation */
}
```

### Include Order
```c
/* 1. System/standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 2. Linux/kernel headers (for kernel modules) */
#include <linux/module.h>
#include <linux/kernel.h>

/* 3. Local project headers */
#include "list.h"
#include "utils.h"
```

---

## Functions

### Function Length
```c
/* Keep functions focused and concise (generally <50 lines)
 * If longer, consider breaking into smaller functions */

// BAD: Too long, does too many things
void process_order(struct order *order) {
    // 100+ lines of mixed validation, processing, logging...
}

// GOOD: Broken into logical pieces
void process_order(struct order *order) {
    if (!validate_order(order)) {
        return;
    }
    update_inventory(order);
    charge_customer(order);
    send_confirmation(order);
}

static int validate_order(struct order *order) {
    return order->items != NULL && order->customer != NULL;
}
```

### Function Parameters
```c
/* Limit function parameters (≤5 is ideal, ≤7 maximum) */

// BAD: Too many parameters
void create_user(char *username, char *email, char *password,
                 char *first_name, char *last_name,
                 char *phone, char *address, char *city);

// GOOD: Group related data into structs
struct user_profile {
    char *first_name;
    char *last_name;
    char *phone;
    char *address;
    char *city;
};

void create_user(char *username, char *email, char *password,
                 struct user_profile *profile);
```

### Return Values
```c
/* Always check return values from functions that can fail */

// BAD: Ignoring return value
malloc(100);

// GOOD: Check for errors
int *data = malloc(100 * sizeof(int));
if (data == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return -1;
}
```

### Early Returns for Error Handling
```c
/* Use guard clauses for validation (early returns) */

int process_data(int *data, int size) {
    /* Guard clauses for validation */
    if (data == NULL) {
        return -1;
    }
    if (size <= 0) {
        return -1;
    }

    /* Main logic after validation */
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += data[i];
    }
    return result;
}
```

---

## Documentation

### File Header Comments
```c
/*
 * list.c - Linked list implementation
 *
 * Authors: Josh Manchester and Ronan Hella
 * Course: CS4500 - Operating Systems
 * Date: February 23, 2025
 *
 * This module implements a singly-linked list data structure
 * that stores dynamically allocated strings. Each node contains
 * a string pointer and a pointer to the next node.
 */
```

### Function Comments
```c
/*
 * calculate_free_slots - Calculate free 30-minute time slots for a date
 *
 * @date: Date to check for free slots
 * @unavailabilities: Array of unavailability periods
 * @count: Number of unavailability periods
 * @start_hour: Starting hour for schedule (e.g., 8 for 8 AM)
 * @end_hour: Ending hour for schedule (e.g., 20 for 8 PM)
 *
 * Returns: Number of free slots, or -1 on error
 *
 * This function divides the time range into 30-minute slots and
 * determines which slots are not covered by any unavailability period.
 */
int calculate_free_slots(date_t date, struct unavail *unavailabilities,
                         int count, int start_hour, int end_hour) {
    /* Implementation */
}
```

### Inline Comments
```c
/* Use comments to explain WHY, not WHAT */

// BAD: Comment states the obvious
counter++; // Increment counter

// GOOD: Comment explains reasoning
counter++; // Account for zero-based indexing in array

// BAD: Redundant comment
int *ptr = malloc(100); // Allocate memory

// GOOD: Explains business logic
// List maintains insertion order; add to tail not head
append_to_tail(list, item);

/* Use TODO comments for future improvements */
// TODO(username): Add support for variable-length strings
char buffer[256];

/* Use FIXME for known issues */
// FIXME(username): Memory leak if allocation fails mid-loop
for (i = 0; i < count; i++) {
    data[i] = malloc(100);
}
```

---

## Error Handling

### Check All Allocations
```c
// ALWAYS check malloc/calloc/realloc return values

// BAD
int *data = malloc(100 * sizeof(int));
data[0] = 42; // Crash if malloc failed!

// GOOD
int *data = malloc(100 * sizeof(int));
if (data == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    return NULL;
}
data[0] = 42;
```

### Validate Function Arguments
```c
int add_to_list(list *ll, char *item) {
    /* Validate inputs at function entry */
    if (ll == NULL || item == NULL) {
        fprintf(stderr, "Error: NULL argument passed to add_to_list\n");
        return -1;
    }

    /* Main logic */
    // ... implementation
    return 0;
}
```

### Error Messages
```c
/* Error messages should be clear and actionable */

// BAD
fprintf(stderr, "Error\n");

// GOOD
fprintf(stderr, "Error: Failed to allocate memory for list node\n");

// GOOD with context
fprintf(stderr, "Error: Invalid time range - start_time (%d) must be "
                "before end_time (%d)\n", start_time, end_time);
```

---

## Header Files

### Header Guard Pattern
```c
/* Use include guards to prevent multiple inclusion */

// list.h
#ifndef LIST_H
#define LIST_H

/* Header contents */

#endif /* LIST_H */
```

### Header Organization
```c
#ifndef LIST_H
#define LIST_H

/* System includes needed by header */
#include <stdio.h>

/* Type definitions */
typedef struct Node node;

struct Node {
    char *item;
    node *next;
};

typedef struct List {
    node *head;
} list;

/* Function prototypes with brief descriptions */

/*
 * createlist - Allocate and initialize a new list
 *
 * Returns: Pointer to new list, or NULL on error
 */
list *createlist(void);

/*
 * addtolist - Add a string to the end of the list
 *
 * @ll: List to add to
 * @item: String to add (will be copied)
 *
 * Returns: 0 on success, -1 on error
 */
int addtolist(list *ll, char *item);

#endif /* LIST_H */
```

### What Goes in Headers
```c
/* INCLUDE in headers: */
- Function prototypes
- Type definitions (struct, typedef, enum)
- Macro definitions
- Extern declarations

/* EXCLUDE from headers: */
- Function implementations (except inline)
- Variable definitions (use extern declarations instead)
- Static functions (file-local only)
```

---

## Memory Management

### Allocation and Deallocation
```c
/* Every malloc must have a corresponding free */

// GOOD pattern
char *str = strdup(source);
if (str == NULL) {
    return -1;
}
// ... use str ...
free(str);
str = NULL; // Good practice to prevent use-after-free

/* Free in reverse order of allocation dependencies */
node *n = malloc(sizeof(node));
n->item = strdup("test");

// Later...
free(n->item); // Free string first
free(n);       // Then free node
```

### Avoiding Memory Leaks
```c
/* BAD: Memory leak on error path */
int process_data(void) {
    int *data = malloc(100 * sizeof(int));
    if (some_error_condition) {
        return -1; // LEAK! data not freed
    }
    free(data);
    return 0;
}

/* GOOD: Free on all paths */
int process_data(void) {
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) {
        return -1;
    }

    if (some_error_condition) {
        free(data); // Free before returning
        return -1;
    }

    free(data);
    return 0;
}

/* BETTER: Use goto for cleanup (common in kernel code) */
int process_data(void) {
    int ret = -1;
    int *data = malloc(100 * sizeof(int));
    if (data == NULL) {
        goto out;
    }

    if (some_error_condition) {
        goto out_free;
    }

    ret = 0;

out_free:
    free(data);
out:
    return ret;
}
```

### Double Free Prevention
```c
/* Set pointers to NULL after freeing */
free(ptr);
ptr = NULL; // Prevents accidental double-free

/* Function that frees and nullifies */
void freelist(list **ll) {
    if (ll == NULL || *ll == NULL) {
        return;
    }

    flushlist(*ll); // Free contents
    free(*ll);      // Free structure
    *ll = NULL;     // Nullify caller's pointer
}
```

---

## Kernel Module Specifics

### Follow Linux Kernel Style
```c
/* For kernel modules, follow Linux kernel coding style:
 * - Use tabs for indentation (not spaces)
 * - Opening brace on next line for functions
 * - Use printk, not printf
 */

#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello world!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Hello World Module");
```

### Kernel Module Best Practices
```c
/* Always specify log level with printk */
printk(KERN_INFO "Informational message\n");  // GOOD
printk("Message\n");                          // BAD - no log level

/* Check for errors in init function */
static int __init mymodule_init(void)
{
	int ret;

	ret = register_something();
	if (ret < 0) {
		printk(KERN_ERR "mymodule: Registration failed\n");
		return ret;
	}

	printk(KERN_INFO "mymodule: Loaded successfully\n");
	return 0;
}

/* Clean up properly in exit function */
static void __exit mymodule_exit(void)
{
	unregister_something();
	printk(KERN_INFO "mymodule: Unloaded\n");
}
```

---

## Makefiles

### Standard Makefile Structure
```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = list_test

# Source files
SRCS = list.c list_test.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
```

### Kernel Module Makefile
```makefile
# Kernel module makefile format
obj-m += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

.PHONY: all clean
```

### Makefile Best Practices
```makefile
# CRITICAL: No spaces in paths or around = in M=$(PWD)
# GOOD
M=$(PWD)

# BAD - will fail
M = $(PWD)

# Use tabs for indentation in commands (not spaces)
all:
→   $(CC) -o program main.c    # This is a tab (→), not spaces

# Use .PHONY for non-file targets
.PHONY: all clean test
```

---

## Code Review Checklist

### Before Committing
- [ ] Code compiles without warnings (`-Wall -Wextra`)
- [ ] All functions have comment blocks
- [ ] All memory allocations are checked
- [ ] All allocated memory is freed
- [ ] No memory leaks (run valgrind)
- [ ] File names follow naming conventions
- [ ] Consistent indentation (4 spaces for user-space, tabs for kernel)
- [ ] No trailing whitespace
- [ ] README/documentation updated if needed

### Reviewing Code
- [ ] Code follows this style guide
- [ ] Function names are descriptive
- [ ] Error conditions are handled properly
- [ ] No magic numbers (use named constants)
- [ ] Proper NULL checks before dereferencing pointers
- [ ] Buffer sizes are validated
- [ ] Code is maintainable and readable

---

## Resources

- [Linux Kernel Coding Style](https://www.kernel.org/doc/html/latest/process/coding-style.html)
- [GNU Coding Standards](https://www.gnu.org/prep/standards/standards.html)
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [SEI CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard)

---

## Changelog

### Version 1.0 (November 2, 2025)
- Initial C style guide creation for CS4500
- Adapted from CS3300 Python/Django style guide
- Added C-specific conventions for user-space and kernel code
- Established file naming standards
- Added memory management guidelines
- Added kernel module specific guidelines

---

**Questions or Suggestions?**
This guide is a living document and will evolve with the project. Follow these standards to ensure code consistency across the CS4500 codebase.
