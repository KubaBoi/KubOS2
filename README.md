# Install

- sudo apt-get install g++ binutils libc6-dev-i386
- sudo apt-get install VirtualBox grub-legacy xorriso

# neco

(killall VirtualBox && sleep 1) || true

VirtualBox --startvm '$(OSNAME)' &