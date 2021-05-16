#sudo apt-get install g++ binutils libc6-dev-i386 xorriso
#make kernel.o
#make loader.o
#make mykernel.bin
#make mykernel.iso

OSNAME = KubOS
LIBDIR := lib
SRCDIR := src
BUILDDIR := bin

GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = $(LIBDIR)/loader.o $(LIBDIR)/interruptstubs.o $(LIBDIR)/gdt.o $(LIBDIR)/port.o $(LIBDIR)/kernel.o $(LIBDIR)/interrupts.o $(LIBDIR)/keyboard.o 

%.o: $(SRCDIR)/%.cpp
	gcc $(GCCPARAMS) -c -o $(LIBDIR)/$@ $<

%.o: %.s
	as $(ASPARAMS) -o $(LIBDIR)/$@ $<

$(OSNAME).bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $(BUILDDIR)/$@ $(objects)

$(OSNAME).iso: $(BUILDDIR)/$(OSNAME).bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "KubOS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/$(OSNAME).bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(BUILDDIR)/$@ iso
	rm -rf iso
	
run: $(BUILDDIR)/$(OSNAME).iso
	qemu-system-x86_64 -boot d -cdrom $(BUILDDIR)/$(OSNAME).iso -m 512

.PHONY: clean
clean:
	rm -f $(objects) $(BUILDDIR)/$(OSNAME).bin $(BUILDDIR)/$(OSNAME).iso
	