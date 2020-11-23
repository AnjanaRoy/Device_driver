#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static char* charvar = "module";
static int intvar = 10;


module_param(charvar, charp, S_IRUGO);
module_param(intvar, int, S_IRUGO);

static int init_dev(void)  
{
    printk(KERN_ALERT"We are in init function\n");
    printk( "The value of charvar is: %s\n", charvar);
    printk( "the value of intvar is : %d\n",intvar);

    return 0;
}

static void exit_dev(void ) {
    printk(KERN_ALERT "removing module.. you will never see me again\n");
}

module_init(init_dev);
module_exit(exit_dev);
