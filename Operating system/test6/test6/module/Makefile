obj-m := hello.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:= /usr/src/linux-4.16.10
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
