#include <linux/module.h>
#include <linux/time.h>

#define UTC_ET_OFF -5*60*60

static int hello_init(void) {
   printk("Hello World  , we are Dario and Marcelo\n");
   printk("Hello World 1, we are Dario and Marcelo\n");
   printk("Hello World 2, we are Dario and Marcelo\n");

   return 0;
   
}

static void hello_exit(void) {
   printk("Goodbye World  , we are Dario and Marcelo\n");
   printk("Goodbye World 1, we are Dario and Marcelo\n");
   printk("Goodbye World 2, we are Dario and Marcelo\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Dario and Marcelo");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello World, we are Dario and Marcelo");
