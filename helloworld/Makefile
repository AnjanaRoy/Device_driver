obj-m := hello.o

#KRNELDIR=/lib/modules/$(shell unam -r)/build/
KERNELDIR=/usr/src/linux-headers-5.3.0-45-generic/

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean