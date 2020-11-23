#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int add( int , int);

static int total;
static int int1=0;
static int int2=0;

module_param(int1, int , S_IRUGO);
module_param(int2, int , S_IRUGO);

static int init_total(void)
{
    printk(KERN_ALERT"inti done");
    total = add(int1, int2);
    printk("total of two given numbers is %d\n",total);
    return 0;
}

static void exit_total(void )  
{
    printk(KERN_ALERT"exit done\n");
}


module_init(init_total);
module_exit(exit_total);