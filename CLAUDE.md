# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a CS4500 (Operating Systems) course repository containing C programming projects focused on:
- Data structures (linked lists)
- Linux kernel module development
- Process management and system calls
- Python assignments for operating systems concepts

## Coding Standards

All C code in this repository follows the **STYLE_GUIDE.md** conventions. Key standards:

### File Naming
- **C source files**: lowercase_with_underscores.c (e.g., `list.c`, `print_other.c`)
- **Header files**: lowercase_with_underscores.h (e.g., `list.h`)
- **Documentation**: ALL CAPS with extension (e.g., `README.txt`, `README.md`)
- **Makefiles**: Capitalized `Makefile` (standard convention)

### Code Style
- **Indentation**: 4 spaces for user-space C, tabs for kernel modules (Linux kernel style)
- **Line length**: Maximum 100 characters
- **Braces**: K&R style for user-space (opening brace on same line), Linux kernel style for modules (opening brace on next line)
- **Comments**: Explain WHY, not WHAT; all functions must have comment blocks
- **Memory**: Always check malloc/calloc return values; free all allocated memory; verify with valgrind

### Function Conventions
- Use descriptive names with verb_noun pattern: `create_list()`, `add_to_list()`
- Keep functions focused (<50 lines ideal)
- Validate inputs at function entry (guard clauses)
- Use early returns for error conditions

See **STYLE_GUIDE.md** for complete coding standards and examples.

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

### Code Quality and Linting

All C code is analyzed with multiple static analysis tools via WSL Ubuntu:

#### Running Linters

**gcc with strict warnings** (for user-space C code):
```bash
wsl bash -c "cd /mnt/c/Users/manch/OneDrive/Desktop/CS4500/project_01 && \
  gcc -Wall -Wextra -Wpedantic -Wformat=2 -Wshadow -c list.c -o /tmp/list.o"
```

**cppcheck static analyzer** (comprehensive checking):
```bash
wsl bash -c "cd /mnt/c/Users/manch/OneDrive/Desktop/CS4500/project_01 && \
  cppcheck --enable=all --suppress=missingIncludeSystem list.c list_test.c"
```

**clang-format** (code formatting):
```bash
wsl bash -c "cd /mnt/c/Users/manch/OneDrive/Desktop/CS4500/project_01 && \
  clang-format -i list.c"
```

#### Code Quality Standards
- **Zero warnings**: All user-space C code must compile with `-Wall -Wextra -Wpedantic -Wformat=2 -Wshadow`
- **cppcheck clean**: No issues reported by cppcheck static analyzer
- **Const correctness**: Function parameters that don't modify input should use `const`
- **No memory leaks**: Verify with valgrind (when available)

#### Known Limitations
- Kernel modules cannot be linted with standard gcc/cppcheck as they require Linux kernel headers
- Kernel modules should be built with `make` to check for compilation errors
- Use `sparse` or kernel-specific checkers for kernel module analysis if needed

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
