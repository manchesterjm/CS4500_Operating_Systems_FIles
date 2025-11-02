Project 02 Part 4 README File (Kernel Modules and System Calls)
-----------------------------------------------------------------

Authors:
  Josh Manchester and Ronan Hella

Disclaimer:
  We have neither given nor received unauthorized assistance on this work.

Directory and Name of VM:
  Name: Josh_Ronan
  Located under jmanches profile

Path of files in VM:
  /home/josh/Public/Project_01/project_02/part_4

Description:
  This part is a written report addressing conceptual questions related to kernel
  modules and system calls. No code is provided for this part. The questions addressed are:

  1. What is the difference between a kernel module and a system call?
     - A kernel module is dynamically loadable code that extends the functionality of
       the kernel (e.g., drivers, file systems) without requiring a reboot.
     - A system call is a fixed, statically defined interface within the kernel that allows
       user-space applications to request services (like file I/O, process management) from the kernel.
  
  2. Reflection on a 20-year-old kernel module example:
     - Although the basic concept of kernel modules remains the same, modern kernels have
       significantly updated APIs, security measures (e.g., module signing), and improved
       stability and performance.
     - Legacy examples may fail to compile or run due to changes such as renamed structure fields
       (e.g., task_struct state field) and stricter policies, but these changes are beneficial
       overall as they improve system security and reliability.

Files:
  - README.txt : This file containing the written answers for Part 4.

Compilation and Running:
  No compilation is necessary for Part 4 as it is a written report component, not a code module.

Cleaning Up:
  Not applicable.

Challenges and Notes:
  - The challenge was to clearly articulate the differences between dynamically loadable kernel modules
    and the fixed interfaces provided by system calls.
  - Understanding the evolution of kernel APIs helped in explaining why some legacy examples may no longer work.

Resources:
  - The Linux Kernel Module Programming Guide
  - Lecture materials on kernel development and system calls
  - Various online articles discussing the evolution of Linux kernel APIs
