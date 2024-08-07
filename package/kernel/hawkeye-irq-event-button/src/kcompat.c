#include "kcompat.h"

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 6)
/**
 * of_irq_get - Decode a node's IRQ and return it as a Linux irq number
 * @dev: pointer to device tree node
 * @index: zero-based index of the irq
 *
 * Returns Linux irq number on success, or -EPROBE_DEFER if the irq domain
 * is not yet created.
 *
 */
int of_irq_get(struct device_node *dev, int index)
{
	int rc;
	struct of_phandle_args oirq;
	struct irq_domain *domain;

	rc = of_irq_parse_one(dev, index, &oirq);
	if (rc)
		return rc;

	domain = irq_find_host(oirq.np);
	if (!domain)
		return -EPROBE_DEFER;

	return irq_create_of_mapping(&oirq);
}
#endif
