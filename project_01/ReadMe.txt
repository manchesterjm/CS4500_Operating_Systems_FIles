Project 1 README file

Authors:
-------
Josh Manchester and Ronan Hella

Disclaimer:
----------
We have neither given nor received unauthorized assistance on this work 

Directory and Name of VM:
-------------------
Name - Josh_Ronan
located under jmanches profile

Path of code in VM:
-----------------------------
/home/josh/Public/Project_01/project_01

User Name and PSWD:
-------------------
josh
KMJNkmjn9090

Description:
-------------
This project implements a simple linked list data structure in C.
Each node in the list stores a dynamically allocated string and a pointer
to the next node. This was taught in CS2060 and the code from the final
assignment was reused for this one. The following functionalities are provided.

From the List.h we have:

 - Creating a new list (createlist)
 - Adding a string to the end of the list (addtolist)
 - Removing the head node from the list (removefromlist)
 - Printing all items in the list (printlist)
 - Flushing (clearing) the list (flushlist)
 - Freeing the entire list (freelist)

Files:
------
list.h        - Provided header file containing struct definitions and function prototypes.
list.c        - Source file with implementations of the linked list functions.
list_test.c   - Test file that demonstrates and tests the linked list functionality.
makefile      - Makefile to compile the project.
ReadMe.txt    - This file.

Compilation and Running:
--------------------------
To compile the program, run:
    make
This will compile the source files and produce an executable named "list_test".

To run the program, execute:
    ./list_test

Cleaning Up:
-------------
To remove the compiled files, run:
    make clean

Challenges and Notes:
----------------------
- Memory management: Special care was taken to allocate and free memory properly.
	-- This was a big deal in CS2060
- Edge Cases: The code checks for NULL pointers and handles empty lists gracefully.
- The use of strdup simplifies string copying; if unavailable, you can replace it with
  malloc, strlen, and strncpy.
- Testing using list_test.c demonstrates the functionality of each operation.

Resources:
----------
- Standard C library documentation.
- Discussions with team members and prior course materials helped clarify pointer and
  memory management.
