Project 02 Part 1 README File (HelloWorld Kernel Module)
----------------------------------------------------------

Authors:
  Josh Manchester and Ronan Hella

Disclaimer:
  We have neither given nor received unauthorized assistance on this work.

Directory and Name of VM:
  Name: Josh_Ronan
  Located under jmanches profile

Path of Code in VM:
  /home/josh/Public/Project_01/project_02/part_1

User Name and Password:
  Username: josh
  Password: KMJNkmjn9090

Description:
  This part implements a simple "Hello World" Linux kernel module. When loaded,
  the module prints "Hello world!" to the kernel log using printk, and when removed,
  it prints "Goodbye world!" This demonstrates the basics of writing, compiling,
  loading, and unloading a kernel module.

Files:
  - hello.c    : Source file for the Hello World module.
  - Makefile   : To compile the module.
  - README.txt : This file.

Compilation and Running:
  1. Open a terminal and navigate to the part_1 directory:
       cd /home/josh/Public/Project_01/project_02/part_1
  2. Compile the module:
       make
     (This will produce hello.ko)
  3. Load the module into the kernel:
       sudo insmod hello.ko
  4. View the module output:
       sudo dmesg -T | tail
  5. Remove the module from the kernel:
       sudo rmmod hello
  6. Verify removal by checking the output:
       sudo dmesg -T | tail

Cleaning Up:
  To remove compiled files, run:
       make clean

Challenges and Notes:
  - Special care was taken to type the printk messages to avoid encoding issues.
  - Warnings about compiler differences can be safely ignored.

Resources:
  - The Linux Kernel Module Programming Guide
  - Lecture slides and online documentation regarding kernel modules
