#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/moduleparam.h>

/* use this to pass a PID that is running to the kernel module
   sudo insmod print_other.ko target_pid=1234
   where 1234 is the PID we want to target
   find a valid PID by running
   ps -e -o pid,ppid,cmd
   or pgrep bash to get bash PID
*/

static int target_pid = 1;  // Default PID (init/systemd) it will be overriden when we run the command above
module_param(target_pid, int, 0644); // 0644 is the permission mode for read/write parameters
MODULE_PARM_DESC(target_pid, "Target process ID");

// Function Prototypes
int print_other_init(void);
void print_other_exit(void);

// Module Initialization
int print_other_init(void) {
    struct task_struct *task;

    printk(KERN_INFO "print_other: Searching for PID %d\n", target_pid);

    // Use pid_task(find_vpid(pid), PIDTYPE_PID) to safely retrieve the task struct
    task = pid_task(find_vpid(target_pid), PIDTYPE_PID);

    // Handle case where process is not found
    if (!task) {
        printk(KERN_INFO "print_other: Process with PID %d not found.\n", target_pid);
        return -ESRCH; // Error, no such process exists, included in kernel.h
    }

    // Print target process info
    printk(KERN_INFO "print_other: Target Process: %s (PID: %d, State: %u)\n",
           task->comm, task->pid, task->__state);

    // Traverse parent hierarchy safely
    while (task->parent && task->pid != 1) {  // Stop at PID 1 (init/systemd)
        task = task->parent;
        printk(KERN_INFO "print_other: Parent Process: %s (PID: %d, State: %u)\n",
               task->comm, task->pid, task->__state);
    }

    return 0;
}

// Module Cleanup
void print_other_exit(void) {
    printk(KERN_INFO "print_other: Unloading module\n");
}

module_init(print_other_init);
module_exit(print_other_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Josh");
MODULE_DESCRIPTION("Kernel module to print details of an arbitrary process by PID using pid_task(find_vpid(), PIDTYPE_PID)");
