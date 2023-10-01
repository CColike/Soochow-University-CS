obj-m:=readpfcount.o
KDIR:=/usr/src/linux-$(shell uname -r | cut -d '-' -f1)
PWD:= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
