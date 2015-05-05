#include <linux/module.h>
#include <linux/init.h>
#include <linux/pm_qos.h>
#include <linux/workqueue.h>
#include "backports.h"

MODULE_AUTHOR("Luis R. Rodriguez");
MODULE_DESCRIPTION("Kernel backport module");
MODULE_LICENSE("GPL");

#ifndef BACKPORTED_KERNEL_NAME
#error "You need a BACKPORTED_KERNEL_NAME"
#endif

#ifndef BACKPORTED_KERNEL_VERSION
#error "You need a BACKPORTED_KERNEL_VERSION"
#endif

#ifndef BACKPORTS_VERSION
#error "You need a BACKPORTS_VERSION"
#endif

void backport_dependency_symbol(void)
{
}
EXPORT_SYMBOL_GPL(backport_dependency_symbol);


static int __init backport_init(void)
{
	int ret = crypto_ccm_module_init();
	if (ret)
		return ret;

	dma_buf_init();

	printk(KERN_INFO "Loading modules backported from " BACKPORTED_KERNEL_NAME
#ifndef BACKPORTS_GIT_TRACKED
		" version " BACKPORTED_KERNEL_VERSION
#endif
		"\n");
#ifdef BACKPORTS_GIT_TRACKED
	printk(KERN_INFO BACKPORTS_GIT_TRACKED "\n");
#else
	printk(KERN_INFO "Backport generated by backports.git " BACKPORTS_VERSION "\n");
#endif

        return 0;
}
subsys_initcall(backport_init);

static void __exit backport_exit(void)
{
	crypto_ccm_module_exit();
}
module_exit(backport_exit);