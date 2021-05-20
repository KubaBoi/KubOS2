
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso

OSNAME = KubOS

GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/loader.o \
          obj/gdt.o \
          obj/drivers/driver.o \
          obj/hardwarecommunication/port.o \
          obj/hardwarecommunication/interruptstubs.o \
          obj/hardwarecommunication/interrupts.o \
          obj/drivers/keyboard.o \
          obj/drivers/mouse.o \
          obj/kernel.o


run: $(OSNAME).iso
	qemu-system-x86_64 -boot d -cdrom $(OSNAME).iso -m 512

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

$(OSNAME).bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

$(OSNAME).iso: $(OSNAME).bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $(OSNAME).bin iso/boot/$(OSNAME).bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "KubOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/$(OSNAME).bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(OSNAME).iso iso
	rm -rf iso

.PHONY: clean
clean:
	rm -rf obj $(OSNAME).bin $(OSNAME).iso
