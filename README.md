# Install

- sudo apt install g++ binutils libc6-dev-i386
- sudo apt install xorriso
- sudo apt install make
- sudo apt install grub-common

# neco

(killall VirtualBox && sleep 1) || true

VirtualBox --startvm '$(OSNAME)' &