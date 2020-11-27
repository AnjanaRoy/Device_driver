#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DD");

static dev_t devnum; //device number 
static struct cdev _cdev; //represent char device

static int Sample_open(struct inode *inodep,struct file *filep)
{
    printk("Sample open function\n");
    return 0;
}
static int Sample_close(struct inode *inodep,struct file *filep)
{
    printk("Sample close function\n");
    return 0;
}

struct file_operations fops={
    .open = Sample_open,
    .release = Sample_close,
};
static int __init Sample_init(void)
{
    int ret;
    devnum =MKDEV(42,0);   //used for constructing device number
    ret = register_chrdev_region(devnum,1,"Sample_dev"); //rqst for kernel
    if(ret)
    {
        printk("Kernel didn't grant us device number\n");
        return ret;
    }

    cdev_init(&_cdev, &fops); //bind ur cdev with file operation
    ret =cdev_add(&_cdev,devnum,1); //device is live now
    if(ret)
    {
        printk("unable to add cdev to kernel\n");
        unregister_chrdev_region(devnum,1);
        return ret;
    }
    printk("init done\n");
    return 0;
}

static void __exit sample_exit(void)
{
    cdev_del(&_cdev);
    unregister_chrdev_region(devnum,1);
    printk("Good bye\n");
}

module_init(Sample_init);
module_exit(sample_exit);