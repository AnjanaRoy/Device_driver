#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#define SIZE 32

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DD");

static dev_t devnum; //device number 
static struct cdev _cdev; //represent char device
static struct circ_buf cbuf; //represent circular buffer

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
static ssize_t Sample_read (struct file *fp, char __user *Ubuff, size_t count, loff_t *offset)
{
    int i,ret, mini;
    mini = min(count, (size_t)CIRC_CNT(cbuf.head, cbuf.tail, SIZE));
    printk("\nsize recive from user to read : %d",(int)count);
    for(i=0; i<mini; i++)
    {
        ret = copy_to_user(Ubuff+i, cbuf.buf + cbuf.tail,1);
        if(ret)
        {
             printk("Error in coping from user");
            return -EFAULT;
        }
        cbuf.tail=(cbuf.tail+1) & (SIZE-1);
        printk("copy %c to user",Ubuff[i]);
        
    }
    return i;
}

static ssize_t Sample_write (struct file *fp, const char __user *Ubuff, size_t count, loff_t *offset)
{
    int ret,i,mini;
    mini = min(count, (size_t)CIRC_CNT(cbuf.head, cbuf.tail, COUNT));
    printk("\nsize sent from user : %d", (int)count);
    for(i=0; i<mini; i++)
    {
        ret = copy_from_user(cbuf.buf + cbuf.head, Ubuff+i,1);
        if(ret)
        {
            printk("Error in coping file");
            return -EFAULT;
        }
        printk("copied from user: %c", cbuf.buf[cbuf.head]);
        cbuf.head = (cbuf.head+1) & (SIZE-1);
        
    }
    return i;
}

struct file_operations fops={
    .open = Sample_open,
    .release = Sample_close,
    .read = Sample_read,
    .write = Sample_write,
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

    cbuf.buf=kmalloc(SIZE, GFP_KERNEL);
    if(!cbuf.buf)
    {
        printk("memory not allocated");
        unregister_chrdev_region(devnum,1);
        return -1;
    }

    cdev_init(&_cdev, &fops); //bind ur cdev with file operation
    ret =cdev_add(&_cdev,devnum,1); //device is live now
    if(ret)
    {
        printk("unable to add cdev to kernel\n");
        //kfree(cbuf.buf);
        unregister_chrdev_region(devnum,1);
        return ret;
    }
    printk("init done\n");
    return 0;
}

static void __exit Sample_exit(void)
{
    cdev_del(&_cdev);
    kfree(cbuf.buf);
    unregister_chrdev_region(devnum,1);
    printk("Good bye\n");
}

module_init(Sample_init);
module_exit(Sample_exit);