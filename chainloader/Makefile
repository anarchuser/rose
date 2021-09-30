# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Cross-compiler
ARMGNU ?= aarch64-linux-gnu

# Options for C, Asembly, and the linker, respectively
COPS   = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude
LOPS   = -ffreestanding -nostdlib

# Mount point and boot partition
MNT = build/mnt
BOOT_PART = /dev/mmcblk0p1

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

# Default target (invoked by `make` or `make build`). Produces 'chainloader.img' which can then be booted from
build: clean chainloader.img

# Build kernel executable and linkable file where we can extract the kernel from
chainloader.elf: $(OBJECTS) $(SRC)/linker.ld
	$(ARMGNU)-ld -T $(SRC)/linker.ld -o $(BUILD)/chainloader.elf $(OBJECTS)

# Build actual kernel image
chainloader.img: $(SRC)/linker.ld $(OBJECTS) chainloader.elf
	echo $(OBJECTS)
	$(ARMGNU)-objcopy $(BUILD)/chainloader.elf -O binary chainloader.img

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

# Compile lists with the dependencies between objects
DEP_FILES = $(OBJECTS:%.o=%.d)
	-include $(DEP_FILES)

# Mount boot partition of SD card onto set mount point to copy image onto it
flash: chainloader.img
	mkdir -p $(MNT)
	sudo mount $(BOOT_PART) $(MNT)
	sudo cp chainloader.img $(MNT)/kernel8.img
	sudo cp $(SRC)/config.txt $(MNT)
	sudo umount $(MNT)

