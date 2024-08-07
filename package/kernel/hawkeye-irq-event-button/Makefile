#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=hawkeye-irq-event-button
PKG_RELEASE:=3
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define KernelPackage/hawkeye-irq-event-button
  SUBMENU:=Other modules
  TITLE:=Hawkeye IRQ event button driver
  FILES:=$(PKG_BUILD_DIR)/event_button.ko
  AUTOLOAD:=$(call AutoLoad,30,event_button,1)
  KCONFIG:=
endef

define KernelPackage/hawkeye-irq-event-button/description
  This package offers the event button driver for Hawkeye platform with
IRQ-based button design.
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,hawkeye-irq-event-button))
