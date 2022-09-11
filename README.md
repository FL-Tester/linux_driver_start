# linux_driver_start
##### 环境搭建
vscode的includepath中 添加与开发板一直内核文件的目录
```C
"includePath": [
              "${workspaceFolder}/**",
              "/home/gec/LDD/linux/original_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek/include",
              "/home/gec/LDD/linux/original_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek/arch/arm/include",
              "/home/gec/LDD/linux/original_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek/arch/arm/include/generated"
          ],
```

Makefile的编写
```Makefile
KERNELDIR := /home/gec/LDD/linux/original_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
CURRENT_PATH := $(shell pwd)

obj-m := chrdevbase.o

## 将chrdevbase.o编译为.ko模块
build: kernel_modules
kernel_modules:
    $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
    $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
```

编写好驱动c文件 直接make
编写好程序需要 用 arm-linux-gnueabihf-gcc 
