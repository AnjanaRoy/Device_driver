#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int add (int x, int y)   {
    printk(KERN_ALERT"inside add fun\n");
    return (x+y);
}

EXPORT_SYMBOL(add);

static int init_add(void)
{
    printk(KERN_ALERT"inti done");
    return 0;
}

static void exit_add(void )  
{
    printk(KERN_ALERT"exit done\n");
}

module_init(init_add);
module_exit(exit_add);