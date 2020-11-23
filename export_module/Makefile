obj-m := add.o total.o

#KRNELDIR=/lib/modules/$(shell unam -r)/build/
KERNELDIR = /lib/modules/$(shell uname -r)/build/

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean