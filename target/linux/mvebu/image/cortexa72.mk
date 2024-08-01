define Device/globalscale_mochabin
  $(call Device/Default-arm64)
  DEVICE_VENDOR := Globalscale
  DEVICE_MODEL := MOCHAbin
  SOC := armada-7040
endef
TARGET_DEVICES += globalscale_mochabin

define Device/marvell_armada7040-db
  $(call Device/Default-arm64)
  DEVICE_VENDOR := Marvell
  DEVICE_MODEL := Armada 7040 Development Board
  DEVICE_DTS := armada-7040-db
  IMAGE/sdcard.img.gz := boot-img-ext4 | sdcard-img-ext4 | gzip | append-metadata
endef
TARGET_DEVICES += marvell_armada7040-db

define Device/marvell_armada8040-db
  $(call Device/Default-arm64)
  DEVICE_VENDOR := Marvell
  DEVICE_MODEL := Armada 8040 Development Board
  DEVICE_DTS := armada-8040-db
  IMAGE/sdcard.img.gz := boot-img-ext4 | sdcard-img-ext4 | gzip | append-metadata
endef
TARGET_DEVICES += marvell_armada8040-db

define Device/marvell_macchiatobin-doubleshot
  $(call Device/Default-arm64)
  DEVICE_VENDOR := SolidRun
  DEVICE_MODEL := MACCHIATObin
  DEVICE_VARIANT := Double Shot
  DEVICE_ALT0_VENDOR := SolidRun
  DEVICE_ALT0_MODEL := Armada 8040 Community Board
  DEVICE_ALT0_VARIANT := Double Shot
  DEVICE_PACKAGES += kmod-i2c-mux-pca954x
  DEVICE_DTS := armada-8040-mcbin
  SUPPORTED_DEVICES := marvell,armada8040-mcbin-doubleshot marvell,armada8040-mcbin
endef
TARGET_DEVICES += marvell_macchiatobin-doubleshot

define Device/marvell_macchiatobin-singleshot
  $(call Device/Default-arm64)
  DEVICE_VENDOR := SolidRun
  DEVICE_MODEL := MACCHIATObin
  DEVICE_VARIANT := Single Shot
  DEVICE_ALT0_VENDOR := SolidRun
  DEVICE_ALT0_MODEL := Armada 8040 Community Board
  DEVICE_ALT0_VARIANT := Single Shot
  DEVICE_PACKAGES += kmod-i2c-mux-pca954x
  DEVICE_DTS := armada-8040-mcbin-singleshot
  SUPPORTED_DEVICES := marvell,armada8040-mcbin-singleshot
endef
TARGET_DEVICES += marvell_macchiatobin-singleshot

define Device/marvell_clearfog-gt-8k
  $(call Device/Default-arm64)
  DEVICE_VENDOR := SolidRun
  DEVICE_MODEL := Clearfog
  DEVICE_VARIANT := GT-8K
  DEVICE_PACKAGES += kmod-i2c-mux-pca954x kmod-crypto-hw-safexcel
  DEVICE_DTS := armada-8040-clearfog-gt-8k
  SUPPORTED_DEVICES := marvell,armada8040-clearfog-gt-8k
endef
TARGET_DEVICES += marvell_clearfog-gt-8k

define Device/iei_puzzle-m901
  $(call Device/Default-arm64)
  SOC := cn9131
  DEVICE_VENDOR := iEi
  DEVICE_MODEL := Puzzle-M901
  DEVICE_PACKAGES += kmod-rtc-ds1307
endef
TARGET_DEVICES += iei_puzzle-m901

define Device/iei_puzzle-m902
  $(call Device/Default-arm64)
  SOC := cn9132
  DEVICE_VENDOR := iEi
  DEVICE_MODEL := Puzzle-M902
  DEVICE_PACKAGES += kmod-rtc-ds1307
endef
TARGET_DEVICES += iei_puzzle-m902

define Device/hawkeye_hk5130
  $(call Device/Default-arm64)
  BOOT_SCRIPT = hawkeye
  DEVICE_VENDOR := Hawkeye
  DEVICE_MODEL := HK5130
  DEVICE_PACKAGES += wpad-basic-mbedtls kmod-ath11k-pci ath11k-firmware-qcn9074 kmod-hawkeye-hwmon-max6639 kmod-hawkyeve-irq-event-button ipq-wifi-hawkeye_hk5130
  DEVICE_DTS := hk5130 hk5131 hk5140 hk5141
  SOC := cn9132
endef
TARGET_DEVICES += hawkeye_hk5130
