TOOLCHAIN_PREFIX=/usr/leeos_tools_for_linux/bin/
helloworld.o: helloworld.s
	$(TOOLCHAIN_PREFIX)/arm-elf-as -o $@ helloworld.s 

helloworld.elf: helloworld.o
	$(TOOLCHAIN_PREFIX)/arm-elf-ld  -e helloworld -Ttext 0x0 helloworld.o -o $@

helloworld.bin: helloworld.elf
	$(TOOLCHAIN_PREFIX)/arm-elf-objcopy -O binary helloworld.elf $@

helloworld.c.o: helloworld.c
	$(TOOLCHAIN_PREFIX)/arm-elf-gcc -c -o $@ $<

helloworld.c.elf: helloworld.c.o
	$(TOOLCHAIN_PREFIX)/arm-elf-ld  -e helloworld -Ttext 0x0 $< -o $@

helloworld.c.bin: helloworld.c.elf
	$(TOOLCHAIN_PREFIX)/arm-elf-objcopy -O binary helloworld.c.elf $@ && cp helloworld.c.bin helloworld.bin
clean:
	rm -rf *.o
