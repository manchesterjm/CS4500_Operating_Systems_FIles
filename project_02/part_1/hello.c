#include <linux/module.h>
#include <linux/kernel.h>

/* Function Prototypes 
   I had to add these because of errors when trying
   to compile */

int hello_init(void);
void hello_exit(void);

/* Function Implementations
   I had to change the names of the functions
   because these names are already used in the
   kernel and it would not compile.  It is also
   good practice to not reuse names of other
   functions that already exist */
   
int hello_init(void) {
    printk(KERN_INFO "Hello, world!\n");
    return 0;
}

void hello_exit(void) {
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
