#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* Function Prototype */
int print_self_init(void);
void print_self_exit(void);

/* Module Initialization */
int print_self_init(void) {
    struct task_struct *task = current; // Get current process
    printk(KERN_INFO "Current Process Name: %s, PID: %d, State: %u\n", task->comm, task->pid, task->__state);

    /* Trace back to init/systemd, ensuring we don't loop forever */
    while (task->parent && task->pid != 1) {  // ✅ Stop at PID 1
        task = task->parent;
        printk(KERN_INFO "Parent Process Name: %s, PID: %d, State: %u\n", task->comm, task->pid, task->__state);
    }

    return 0;
}

/* Module Cleanup */
void print_self_exit(void) {
    printk(KERN_INFO "Unloading print_self module\n");
}

module_init(print_self_init);
module_exit(print_self_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Josh");
MODULE_DESCRIPTION("Kernel module to print process hierarchy to init/systemd");
