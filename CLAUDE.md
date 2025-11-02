# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a CS4500 (Operating Systems) course repository containing C programming projects focused on:
- Data structures (linked lists)
- Linux kernel module development
- Process management and system calls
- Python assignments for operating systems concepts

## Project Structure

### project_01: Linked List Implementation
- **Language**: C
- **Purpose**: Implements a basic linked list data structure with string storage
- **Key files**:
  - `list.h` - Header with struct definitions and function prototypes
  - `list.c` - Implementation of linked list operations (create, add, remove, print, flush, free)
  - `list_test.c` - Test harness demonstrating functionality

### project_02: Linux Kernel Modules
Contains four parts demonstrating kernel module programming:
- **part_1**: Hello World kernel module (hello.c) - basic module load/unload with printk
- **part_2**: Print Self kernel module (print_self.c) - retrieves current process info and traverses parent process chain
- **part_3**: Print Other kernel module (print_other.c) - accepts PID parameter and prints process hierarchy
- **part_4**: Written report on kernel modules vs system calls (conceptual, no code)

## Build Commands

### project_01 (Linked List)
```bash
cd project_01
make          # Compiles and produces list_test executable
./list_test   # Run the test program
make clean    # Remove compiled files
```

### project_02 (Kernel Modules)
Each part (1-3) has its own Makefile for building kernel modules:

```bash
# General pattern for any part
cd project_02/part_N
make                              # Build the .ko module
sudo insmod <module_name>.ko      # Load module (with params if needed)
sudo dmesg -T | tail              # View kernel log output
sudo rmmod <module_name>          # Unload module
make clean                        # Remove compiled files
```

**Specific examples**:
```bash
# Part 1 (Hello World)
cd project_02/part_1
make
sudo insmod hello.ko
sudo dmesg -T | tail
sudo rmmod hello

# Part 2 (Print Self)
cd project_02/part_2
make
sudo insmod print_self.ko
sudo dmesg -T | tail
sudo rmmod print_self

# Part 3 (Print Other - requires PID parameter)
cd project_02/part_3
make
sudo insmod print_other.ko target_pid=<PID>  # Use pgrep bash or similar to get valid PID
sudo dmesg -T | tail -10
sudo rmmod print_other
```

## Code Architecture Notes

### Linked List (project_01)
- Uses classic C linked list pattern with malloc/free for memory management
- Each node stores a dynamically allocated string via strdup()
- Memory safety is critical: all allocated memory must be freed properly
- The `freelist()` function takes `list **ll` to set the original pointer to NULL after freeing

### Kernel Modules (project_02)
- All modules follow standard Linux kernel module structure with `module_init()` and `module_exit()`
- Uses `printk()` for kernel logging (not printf)
- Process traversal uses the `current` macro and parent pointer chains
- Part 3 demonstrates module parameter usage: `module_param(target_pid, int, 0644)`
- Modern kernel API differences from legacy code:
  - Use `pid_task(find_vpid(target_pid), PIDTYPE_PID)` for process lookup
  - Process state field names may differ across kernel versions

## Important Makefile Notes

### Kernel Module Makefiles
The kernel module Makefiles follow a specific pattern:
```makefile
obj-m += <module_name>.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

**Critical**: No spaces in paths (e.g., `/lib/modules/` not `/ lib / modules /`) and no spaces around `=` in `M=$(PWD)`. The original provided Makefiles had formatting issues that were corrected (see project_02/README_makefile_corrections.txt).

### User-Space C Makefile (project_01)
Standard gcc compilation with:
- `-Wall` for all warnings
- `-g` for debug symbols
- Pattern rules for `.c` to `.o` compilation

## Development Environment

### Current Setup (Windows 11 + WSL)
- **Host OS**: Windows 11
- **Compiler**: gcc via WSL Ubuntu
- **Linter**: clang
- **Version Control**: GitHub CLI (gh)
- **Repository Path**: `C:\Users\manch\OneDrive\Desktop\CS4500`

### Using WSL for Compilation
All C compilation should be done in WSL Ubuntu, not native Windows:

```bash
# Access repository from WSL
cd /mnt/c/Users/manch/OneDrive/Desktop/CS4500

# Compile project_01
cd project_01
make
./list_test

# Compile kernel modules (requires Linux kernel headers in WSL)
cd project_02/part_1
make
```

**Note**: Kernel modules require Linux kernel headers. In WSL, install with:
```bash
sudo apt-get update
sudo apt-get install build-essential linux-headers-$(uname -r)
```

### Using GitHub CLI
Git operations should use the GitHub CLI installed on Windows:

```bash
# From Windows (PowerShell or CMD)
gh repo status
gh pr create
gh issue list

# Standard git commands also work
git status
git add .
git commit -m "message"
git push
```

### Linting with Clang
```bash
# Run clang linter on C files
clang --analyze project_01/list.c
clang-format -i project_01/list.c  # Format code
```

### Original Development Environment
Original coursework was done on a VM:
- **VM Name**: Josh_Ronan (under jmanches profile)
- **Path**: `/home/josh/Public/Project_01/`

## Memory Management Best Practices

When working with C code in this repository:
1. Always check malloc/strdup return values for NULL
2. Free all dynamically allocated memory in proper order (strings before nodes)
3. Use valgrind to check for memory leaks when testing
4. For kernel modules, printk messages help debug without user-space tools
