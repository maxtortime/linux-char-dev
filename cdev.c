#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/string.h>

struct Node {
	int data;
	struct Node* next;
};

static int major; 
static char msg[200];

struct Node* front = NULL;
struct Node* rear = NULL;
char *tk;

// To Enqueue an integer
static void Enqueue(int x) {
	struct Node* temp = 
		(struct Node*)kmalloc(sizeof(struct Node),GFP_KERNEL);
	temp->data =x; 
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

// To Dequeue an integer.
static void Dequeue(void) {
	struct Node* temp = front;
	if(front == NULL) {
		printk("Queue is Empty\n");
		return;
	}
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}

	kfree(temp);
}

static int Front(void) {
	if(front == NULL) {
		printk("Queue is empty\n");
		return;
	}
	return front->data;
}

static void Print(void) {
	struct Node* temp = front;
	while(temp != NULL) {
		printk("%d ",temp->data);
		temp = temp->next;
	}
	printk("\n");
}


static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
    Print();
  	return simple_read_from_buffer(buffer, length, offset, msg, 200);
}


static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
    int count = 0;
    int n = 0;

	if (len > 199)
		return -EINVAL;
    // write to buf from user's msg 
	copy_from_user(msg, buff, len);
	msg[len] = '\0';

    if (strncmp(msg,"enqueue",7) == 0) 
    {
        sscanf(msg+8,"%d",&n); // msg+8 is integer..
        Enqueue(n);
        Print();
    }
    else if (strncmp(msg,"dequeue",7)==0) {
    	Dequeue();
    	Print();
    }
    else if (strncmp(msg,"front",5)==0) {
    	printk("Queue front: %d\n",Front());
    }
                
	return len;
}

static struct file_operations fops = {
	.read = device_read, 
	.write = device_write,
};

static int __init cdevexample_module_init(void)
{
	major = register_chrdev(0, "my_device", &fops);
	if (major < 0) {
     		printk ("Registering the character device failed with %d\n", major);
	     	return major;
	}
	printk("cdev example: assigned major: %d\n", major);
	printk("create node with mknod /dev/cdev_example c %d 0\n", major);
 	return 0;
}

static void __exit cdevexample_module_exit(void)
{
	unregister_chrdev(major, "my_device");
}  

module_init(cdevexample_module_init);
module_exit(cdevexample_module_exit);
MODULE_LICENSE("GPL");
