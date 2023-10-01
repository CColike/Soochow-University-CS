TARGET=example1
KDIR=/usr/src/linux
PWD=/home/kh/test/test11
obj-m := $(TARGET).o
default:
	make -C $(KDIR) M=$(PWD) modules
