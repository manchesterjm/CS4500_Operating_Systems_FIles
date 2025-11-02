Project 02 Part 2 README File (Print Self Kernel Module)
----------------------------------------------------------

Authors:
  Josh Manchester and Ronan Hella

Disclaimer:
  We have neither given nor received unauthorized assistance on this work.

Directory and Name of VM:
  Name: Josh_Ronan
  Located under jmanches profile

Path of Code in VM:
  /home/josh/Public/Project_01/project_02/part_2

User Name and Password:
  Username: josh
  Password: KMJNkmjn9090

Description:
  This module retrieves information about the current user-level process using the
  'current' macro. It prints the process name, PID, and state, then traverses the
  parent process chain, printing similar details for each parent until reaching the
  initial process (init or its modern equivalent). This demonstrates process
  information retrieval and hierarchy traversal within the kernel.

Files:
  - print_self.c  : Source file for the Print Self module.
  - Makefile      : To compile the module.
  - README.txt    : This file.

Compilation and Running:
  1. Open a terminal and navigate to the part_2 directory:
       cd /home/josh/Public/Project_01/project_02/part_2
  2. Compile the module:
       make
     (This will produce print_self.ko)
  3. Load the module:
       sudo insmod print_self.ko
  4. View the module output:
       sudo dmesg -T | tail
  5. Remove the module:
       sudo rmmod print_self
  6. Check removal messages:
       sudo dmesg -T | tail

Cleaning Up:
  To remove compiled files, run:
       make clean

Challenges and Notes:
  - Correct inclusion of updated header files was crucial for the 'current' macro.
  - Adjustments were made to accommodate changes in the process state variable.

Resources:
  - The Linux Kernel Module Programming Guide
  - Linux Gazette article and course lecture notes on process management
