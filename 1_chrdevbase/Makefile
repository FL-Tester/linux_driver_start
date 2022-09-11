KERNELDIR := /home/gec/LDD/linux/original_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek


CURRENT_PATH := $(shell pwd)
obj-m := chrdevbase.o


## 将chrdevbase.o编译为.ko模块
build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean