# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Cross-compiler
ARMGNU ?= aarch64-none-elf

# Resolve Mac / linux issues
HOST_OS = $(shell uname -s)

# Build target
IMAGE_NAME = $(shell basename `pwd`)

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
SERIAL_PORT_Linux      = /dev/$(shell ls /dev | grep ttyUSB    | head -n 2 | tail -n 1)
SERIAL_PORT_Darwin     = /dev/$(shell ls /dev | grep usbserial | head -n 2 | tail -n 1)

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
.PHONY: build clean flash flash-Linux flash-Darwin emulate

# Default target (invoked by `make` or `make build`).
build: $(IMAGE_NAME).img

# Build kernel executable and linkable file where we can extract the kernel from
$(IMAGE_NAME).elf: $(OBJECTS) $(SRC)/linker.ld
	$(ARMGNU)-ld -T $(SRC)/linker.ld -o $(BUILD)/$(IMAGE_NAME).elf $(OBJECTS)

# Build actual kernel image
$(IMAGE_NAME).img: $(SRC)/linker.ld $(OBJECTS) $(IMAGE_NAME).elf
	$(ARMGNU)-objcopy $(BUILD)/$(IMAGE_NAME).elf -O binary $(IMAGE_NAME).img

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

# Compile lists with the dependencies between objects
DEP_FILES = $(OBJECTS:%.o=%.d)
	-include $(DEP_FILES)

# Remove kernel and build directory
clean:
	rm -rf $(BUILD) *.img

# Mount boot partition of SD card onto set mount point to copy image onto it
flash: flash-$(HOST_OS)

flash-Linux: $(IMAGE_NAME).img
	mkdir -p $(MNT)
	sudo mount $(BOOT_PART) $(MNT)
	sudo cp $(IMAGE_NAME).img $(MNT)/kernel8.img
	sudo cp $(SRC)/config.txt $(MNT)
	sync
	sleep 1
	sudo umount $(MNT)

flash-Darwin: $(IMAGE_NAME).img
	cp $(IMAGE_NAME).img $(MNT)/kernel8.img
	cp $(SRC)/config.txt $(MNT)
	sync
	diskutil unmount $(MNT)

send: $(IMAGE_NAME).img
	printf "0: %.8x" $(shell wc -c < $(IMAGE_NAME).img) | xxd -re -g0 > $(SERIAL_PORT)
	cat $(IMAGE_NAME).img > $(SERIAL_PORT)

# Run on qemu
emulate: $(IMAGE_NAME).img
	qemu-img resize $(IMAGE_NAME).img -f raw 4294967296
	qemu-system-aarch64 -cpu cortex-a72 -machine type=raspi3 -m 1024 -kernel $(IMAGE_NAME).img -nographic -serial null -chardev stdio,id=uart1 -serial chardev:uart1 -monitor none

