#ifndef _KCOMPAT_H_
#define _KCOMPAT_H_

#ifndef LINUX_VERSION_CODE
#include <linux/version.h>
#else
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/of_irq.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 6)
int of_irq_get(struct device_node *dev, int index);
#endif

#endif // __KCOMPAT_H_
