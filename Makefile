# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Resolve Mac / linux issues
HOST_OS = $(shell uname -s)

# Mount point and boot partition
FLASH_DEFAULT_TARGET = chainloader
MNT = $(MNT_$(HOST_OS))
MNT_Linux  = build/mnt
MNT_Darwin = /Volumes/boot
#BOOT_PART = /dev/mmcblk0p1

# Serial connection config
SEND_DEFAULT_TARGET = thorn
BAUD_RATE = 115200
SERIAL_PORT = $(SERIAL_PORT_$(HOST_OS))
SERIAL_PORT_ALT = $(SERIAL_PORT_ALT_$(HOST_OS))
SERIAL_PORT_Linux      = /dev/$(shell ls /dev | grep ttyUSB    | head -n 2 | tail -n 1)
SERIAL_PORT_ALT_Linux  = /dev/$(shell ls /dev | grep ttyUSB    | head -n 1)
SERIAL_PORT_Darwin     = /dev/$(shell ls /dev | grep usbserial | head -n 2 | tail -n 1)
SERIAL_PORT_ALT_Darwin = /dev/$(shell ls /dev | grep usbserial | head -n 1)

# Building
BUILD_DEFAULT_TARGET = thorn

# Ensure make still works if someone creates a file named like follows:
.PHONY: build clean flash flash-Linux flash-Darwin

# Remove kernel and build directory
clean:
	rm -rf $(BUILD) *.img

cleanall: clean
	$(MAKE) -C chainloader clean
	$(MAKE) -C thorn clean

# Build the different OSes
build: build-$(BUILD_DEFAULT_TARGET)

buildall: build-chainloader build-thorn

build-chainloader:
	$(MAKE) -C chainloader build

build-thorn:
	$(MAKE) -C thorn build

# Mount boot partition of SD card onto set mount point to copy image onto it
flash: flash-$(FLASH_DEFAULT_TARGET)

flash-chainloader:
	$(MAKE) -C chainloader flash

flash-thorn:
	$(MAKE) -C thorn flash

# Send kernel size + kernel
setup-serial-Linux:
	stty -F $(SERIAL_PORT) $(BAUD_RATE) raw cs8 -ixoff -cstopb -parenb

setup-serial-Darwin:
	stty -f $(SERIAL_PORT) $(BAUD_RATE) raw cs8 -ixoff -cstopb -parenb

send: send-$(SEND_DEFAULT_TARGET)

send-chainloader: setup-serial-$(HOST_OS)
	$(MAKE) -C chainloader send

send-thorn: setup-serial-$(HOST_OS)
	$(MAKE) -C thorn send

screen:
	screen $(SERIAL_PORT_ALT) $(BAUD_RATE)
