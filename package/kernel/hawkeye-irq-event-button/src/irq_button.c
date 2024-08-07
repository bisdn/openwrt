/*******************************************************************************

Hawkeye Tech. IRQ-based Event Button Driver
Copyright (C) 2021  Angus <angus@hawkeyetech.com.tw>

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software 
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/hwmon-sysfs.h>
#include <linux/miscdevice.h>

#include "kcompat.h"

struct irq_button_data {
	char name[32];
	int irq;
	struct resource resource;
	int press;
};

#define DRV_NAME "event_button"

#define MAX_IRQ_BUTTONS 16

#define SDA_ATTR &sda->dev_attr.attr

static struct miscdevice mdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DRV_NAME,
};

static struct irq_button_data irq_buttons[MAX_IRQ_BUTTONS];
static struct attribute_group irq_button_defattr_group;

static ssize_t irq_button_sysfs_trigger(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	ssize_t len = 0;

	if (sda->index < MAX_IRQ_BUTTONS) {
		len = sprintf(buf, "%d\n", irq_buttons[sda->index].press);
	} else {
		BUG();
	}

	return len;
}

static ssize_t irq_button_sysfs_clean(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct sensor_device_attribute *sda = to_sensor_dev_attr(attr);

	if (sda->index < MAX_IRQ_BUTTONS) {
		irq_buttons[sda->index].press = 0;
	} else {
		BUG();
	}

	return count;
}

irqreturn_t irq_button_handler(int irq, void *arg)
{
	struct irq_button_data *data = (struct irq_button_data *)arg;

	data->press++;

	return IRQ_HANDLED;
}

struct sensor_device_attribute *create_sda(char *name, umode_t mode,
					   ssize_t (*show)(struct device *dev, struct device_attribute *attr, char *buf),
					   ssize_t (*store)(struct device *dev, struct device_attribute *attr, const char *buf, size_t count),
					   int index)
{
	struct sensor_device_attribute *sda;

	sda = kmalloc(sizeof(struct sensor_device_attribute), GFP_KERNEL);
	sda->dev_attr.attr.name = kmalloc(sizeof(char) * 32, GFP_KERNEL);
	sprintf((char *)sda->dev_attr.attr.name, "%s_%s", irq_buttons[index].name, name);
	sda->dev_attr.attr.mode = mode;
	sda->dev_attr.show = show;
	sda->dev_attr.store = store;
	sda->index = index;

	return sda;
}

static int __init irq_button_init(void)
{
	struct device_node *root, *child;
	struct sensor_device_attribute *sda;
	int i, irq_trigger, button_num = 0;

	root = of_find_compatible_node(NULL, NULL, "hawkeye,irq-buttons");
	if (!root) {
		return -ENODEV;
	}

	/* Register IRQ event */
	for_each_child_of_node(root, child) {
		sprintf(irq_buttons[button_num].name, "%s", child->name);
		irq_buttons[button_num].irq = of_irq_get(child, 0);
		if (irq_buttons[button_num].irq < 0) {
			goto err_irq;
		}

		irq_trigger = irqd_get_trigger_type(irq_get_irq_data(irq_buttons[button_num].irq));
		if (request_irq(irq_buttons[button_num].irq, (irq_handler_t) irq_button_handler, irq_trigger, irq_buttons[button_num].name, &irq_buttons[button_num])) {
			printk(KERN_ERR "%s interrrupt can't register on IRQ%d /n", irq_buttons[button_num].name, irq_buttons[button_num].irq);
			goto err_irq;
		}
		button_num++;
	}

	misc_register(&mdev);

	/* Create sysfs node */
	irq_button_defattr_group.attrs = kmalloc(sizeof(struct attribute **) * (MAX_IRQ_BUTTONS * 2 + 1), GFP_KERNEL);
	for (i = 0; i < button_num; i++) {
		sda = create_sda("trigger", S_IRUGO, irq_button_sysfs_trigger, NULL, i);
		irq_button_defattr_group.attrs[i * 2] = SDA_ATTR;
		sda = create_sda("clean", S_IWUSR, NULL, irq_button_sysfs_clean, i);
		irq_button_defattr_group.attrs[i * 2 + 1] = SDA_ATTR;
	}
	irq_button_defattr_group.attrs[i * 2] = NULL;

	if (sysfs_create_group(&mdev.this_device->kobj, &irq_button_defattr_group)) {
		goto err_sysfs;
	}

	return 0;

err_sysfs:
	misc_deregister(&mdev);
err_irq:
	for (i = 0; i < button_num; i++) {
		free_irq(irq_buttons[i].irq, &irq_buttons[i]);
	}

	return -EIO;
}

static void  __exit irq_button_exit(void)
{
	int i;

	sysfs_remove_group(&mdev.this_device->kobj, &irq_button_defattr_group);

	for (i = 0; i < MAX_IRQ_BUTTONS; i++) {
		if (irq_buttons[i].irq != 0) {
			free_irq(irq_buttons[i].irq, &irq_buttons[i]);
		}
	}

	misc_deregister(&mdev);
}

MODULE_AUTHOR("Angus <angus@hawkeyetech.com.tw>");
MODULE_DESCRIPTION("Hawkeye Tech. IRQ-based Event Button Driver");
MODULE_LICENSE("GPL");

module_init(irq_button_init);
module_exit(irq_button_exit);
