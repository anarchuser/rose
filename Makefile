# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Cross-compiler
ARMGNU ?= aarch64-linux-gnu

# Options for C, Asembly, and the linker, respectively
COPS   = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude
LOPS   = -ffreestanding -nostdlib

# Directories for built files, source files (kernel and common) and header files (include)
BUILD   = build
SRC     = src
KERNEL  = kernel
COMMON  = common
INCLUDE = ./include

# Assemble lists of corresponding source files for assembly, kernel and common
ASM_FILES  = $(wildcard $(SRC)/$(KERNEL)/*.S)
KERNEL_SOURCES = $(wildcard $(SRC)/$(KERNEL)/*.c)
COMMON_SOURCES = $(wildcard $(SRC)/$(COMMON)/*.c)

# Assemble list of compiled objects, correspondingly
OBJECTS  = $(patsubst $(SRC)/$(KERNEL)/%.S, $(BUILD)/$(SRC)/$(KERNEL)/%_S.o, $(ASM_FILES))
OBJECTS += $(patsubst $(SRC)/$(KERNEL)/%.c, $(BUILD)/$(SRC)/$(KERNEL)/%.o, $(KERNEL_SOURCES))
OBJECTS += $(patsubst $(CSRC)/%.c, $(BUILD)/$(CSRC)/%.o, $(COMMON_SOURCES))

# Default target (invoked by `make` or `make all`). Produces 'kernel8.img' which can then be booted from
all: clean kernel8.img

# Build kernel executable and linkable file where we can extract the kernel from
kernel8.elf: $(OBJECTS) $(SRC)/linker.ld
	$(ARMGNU)-ld -T $(SRC)/linker.ld -o $(BUILD)/kernel8.elf $(OBJECTS)

# Build actual kernel image
kernel8.img: $(SRC)/linker.ld $(OBJECTS) kernel8.elf
	echo $(OBJECTS)
	$(ARMGNU)-objcopy $(BUILD)/kernel8.elf -O binary kernel8.img

# All assembly source targets
$(BUILD)/$(SRC)/$(KERNEL)/%_S.o: $(SRC)/$(KERNEL)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# All kernel source targets
$(BUILD)/$(SRC)/$(KERNEL)/%.o: $(SRC)/$(KERNEL)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# All common source targets
$(BUILD)/$(CSRC)/%.o: $(CSRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# Remove kernel and build directory
clean:
	rm -rf $(BUILD) *.img

# Compile lists with the dependencies between objects
DEP_FILES = $(OBJECTS:%.o=%.d)
	-include $(DEP_FILES)
