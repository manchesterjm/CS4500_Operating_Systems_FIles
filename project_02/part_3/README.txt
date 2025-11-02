Project 02 Part 3 README File (Print Other Kernel Module)
-----------------------------------------------------------

Authors:
  Josh Manchester and Ronan Hella

Disclaimer:
  We have neither given nor received unauthorized assistance on this work.

Directory and Name of VM:
  Name: Josh_Ronan
  Located under jmanches profile

Path of Code in VM:
  /home/josh/Public/Project_01/project_02/part_3

User Name and Password:
  Username: josh
  Password: KMJNkmjn9090

Description:
  This module accepts a process PID as a parameter (provided during module insertion)
  and prints the target process’s information (name, PID, state). It then traverses the
  parent process chain, printing details for each parent until reaching the init process
  (PID 1). This exercise demonstrates using module parameters and kernel functions
  like pid_task(find_vpid(target_pid), PIDTYPE_PID) to retrieve process information.

Files:
  - print_other.c : Source file for the Print Other module.
  - Makefile      : To compile the module.
  - README.txt    : This file.

Compilation and Running:
  1. Open a terminal and navigate to the part_3 directory:
       cd /home/josh/Public/Project_01/project_02/part_3
  2. Compile the module:
       make
     (This will produce print_other.ko)
  3. Load the module with a specified PID (replace 1234 with a valid PID, e.g., We used pgrep bash):
       sudo insmod print_other.ko target_pid=1234
  4. View the module output:
       sudo dmesg -T | tail -10
  5. Remove the module:
       sudo rmmod print_other
  6. Verify the output:
       sudo dmesg -T | tail -10

Cleaning Up:
  To remove compiled files, run:
       make clean

Challenges and Notes:
  - Proper passing and parsing of the module parameter was essential.
  - File naming issues were resolved (using .o in the Makefile).
  - Adapted code for changes in process lookup API in modern kernels.

Resources:
  - The Linux Kernel Module Programming Guide
  - Online documentation and lecture notes on module parameters and process lookup
