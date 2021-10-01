# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Resolve Mac / linux issues
HOST_OS = $(shell uname -s)

# Cross-compiler
ARMGNU ?= aarch64-none-elf

# Options for C, Asembly, and the linker, respectively
COPS   = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude
LOPS   = -ffreestanding -nostdlib

# Mount point and boot partition
MNT = $(MNT_$(HOST_OS))
MNT_Linux  = build/mnt
MNT_Darwin = /Volumes/boot
BOOT_PART = /dev/mmcblk0p1

# Serial connection config
BAUD_RATE = 115200
SERIAL_PORT = $(SERIAL_PORT_$(HOST_OS))
SERIAL_PORT_ALT = $(SERIAL_PORT_ALT_$(HOST_OS))
SERIAL_PORT_Linux      = /dev/$(shell ls /dev | grep ttyUSB    | head -n 1)
SERIAL_PORT_ALT_Linux  = /dev/$(shell ls /dev | grep ttyUSB    | head -n 2 | tail -n 1)
SERIAL_PORT_Darwin     = /dev/$(shell ls /dev | grep usbserial | head -n 1)
SERIAL_PORT_ALT_Darwin = /dev/$(shell ls /dev | grep usbserial | head -n 2 | tail -n 1)

# Directories for built files, source files (kernel and common) and header files (include)
BUILD   = build
SRC     = src
KERNEL  = kernel
COMMON  = common
INCLUDE = include

# Assemble lists of corresponding source files for assembly, kernel and common
SRC_KERNEL = $(wildcard $(SRC)/$(KERNEL)/*.c)
ASM_KERNEL = $(wildcard $(SRC)/$(KERNEL)/*.S)
SRC_COMMON = $(wildcard $(SRC)/$(COMMON)/*.c)
ASM_COMMON = $(wildcard $(SRC)/$(COMMON)/*.S)

# Assemble list of compiled objects, correspondingly
OBJECTS  = $(patsubst $(SRC)/$(KERNEL)/%.c, $(BUILD)/$(SRC)/$(KERNEL)/%_c.o, $(SRC_KERNEL))
OBJECTS += $(patsubst $(SRC)/$(KERNEL)/%.S, $(BUILD)/$(SRC)/$(KERNEL)/%_S.o, $(ASM_KERNEL))
OBJECTS += $(patsubst $(SRC)/$(COMMON)/%.c, $(BUILD)/$(SRC)/$(COMMON)/%_c.o, $(SRC_COMMON))
OBJECTS += $(patsubst $(SRC)/$(COMMON)/%.S, $(BUILD)/$(SRC)/$(COMMON)/%_S.o, $(ASM_COMMON))

# Ensure make still works if someone creates a file named like follows:
.PHONY: build build-cl clean cleanall emulate run flash flash-cl flash-os flash-Linux flash-Darwin send setup-serial-Linux setup-serial-Darwin

# Default target (invoked by `make` or `make build`). Produces 'kernel8.img' which can then be booted from
build: kernel8.img

# Build kernel executable and linkable file where we can extract the kernel from
kernel8.elf: $(OBJECTS) $(SRC)/linker.ld
	$(ARMGNU)-ld -T $(SRC)/linker.ld -o $(BUILD)/kernel8.elf $(OBJECTS)

# Build actual kernel image
kernel8.img: $(SRC)/linker.ld $(OBJECTS) kernel8.elf
	$(ARMGNU)-objcopy $(BUILD)/kernel8.elf -O binary kernel8.img

# All kernel source targets
$(BUILD)/$(SRC)/$(KERNEL)/%_c.o: $(SRC)/$(KERNEL)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# All assembly source targets
$(BUILD)/$(SRC)/$(KERNEL)/%_S.o: $(SRC)/$(KERNEL)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# All common source targets
$(BUILD)/$(SRC)/$(COMMON)/%_c.o: $(SRC)/$(COMMON)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# All assembly source targets
$(BUILD)/$(SRC)/$(COMMON)/%_S.o: $(SRC)/$(COMMON)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# Remove kernel and build directory
clean:
	rm -rf $(BUILD) *.img

cleanall: clean
	$(MAKE) -C chainloader clean

# Compile lists with the dependencies between objects
DEP_FILES = $(OBJECTS:%.o=%.d)
	-include $(DEP_FILES)

# Mount boot partition of SD card onto set mount point to copy image onto it
flash: flash-cl # Default whether flash loads kernel or chainloader

flash-os: flash-$(HOST_OS)

flash-cl:
	$(MAKE) -C chainloader flash

flash-Linux: kernel8.img
	mkdir -p $(MNT)
	sudo mount $(BOOT_PART) $(MNT)
	sudo cp kernel8.img $(MNT)
	sudo cp $(SRC)/config.txt $(MNT)
	sudo umount $(MNT)

flash-Darwin: kernel8.img
	cp kernel8.img $(MNT)
	cp $(SRC)/config.txt $(MNT)
	sync
	diskutil unmount $(MNT)

# Run on qemu
emulate: kernel8.img
	qemu-img resize kernel8.img -f raw 4294967296
	qemu-system-aarch64 -cpu cortex-a72 -machine type=raspi3 -m 1024 -kernel kernel8.img -nographic -serial null -chardev stdio,id=uart1 -serial chardev:uart1 -monitor none

# Future target to build and chainload OS
run: kernel8.img
	echo "Not yet implemented"
	exit 1

# Build chainloader
build-cl:
	$(MAKE) -C chainloader build

# Send kernel size + kernel
setup-serial-Linux:
	stty -F $(SERIAL_PORT) $(BAUD_RATE) raw cs8 -ixoff -cstopb -parenb

setup-serial-Darwin:
	stty -f $(SERIAL_PORT) $(BAUD_RATE) raw cs8 -ixoff -cstopb -parenb

send: setup-serial-$(HOST_OS) kernel8.img
	printf "0: %.8x" $(shell wc -c < kernel8.img) | xxd -re -g0 > $(SERIAL_PORT)
	cat kernel8.img > $(SERIAL_PORT)

screen:
	screen $(SERIAL_PORT_ALT) $(BAUD_RATE)