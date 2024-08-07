#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=hawkeye-hwmon-max6639
PKG_RELEASE:=3
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define KernelPackage/hawkeye-hwmon-max6639
  SUBMENU:=Other modules
  TITLE:=Hawkeye MAX6639 hwmon driver
  FILES:=$(PKG_BUILD_DIR)/hk-max6639.ko
  AUTOLOAD:=$(call AutoProbe,hk-max6639)
  DEPENDS:=+kmod-hwmon-core +kmod-i2c-core 
endef

define KernelPackage/hawkeye-hwmon-max6639/description
  Alternative MAX6639 hwmon driver with Hawkeye modifictations.
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,hawkeye-hwmon-max6639))
