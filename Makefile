# | Makefile for the Rose project (github.com/anarchuser/rose)
# | Merged from https://jsandler18.github.io/ and https://github.com/s-matyukevich/raspberry-pi-os

# Cross-compiler
ARMGNU ?= aarch64-linux-gnu

# Options for C and Asembly, respectively
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude 

# Directories for built files, source files (kernel and common) and header files (include)
BUILD_DIR = build
SRC_DIR   = src
KSRC_DIR  = $(SRC_DIR)/kernel
CSRC_DIR  = $(SRC_DIR)/common
HEAD_DIR  = include

# Assemble lists of corresponding source files for assembly, kernel and common
ASM_FILES  = $(wildcard $(KSRC_DIR)/*.S)
KSRC_FILES = $(wildcard $(KSRC_DIR)/*.c)
CSRC_FILES = $(wildcard $(CSRC_DIR)/*.c)

# Assemble list of compiled objects, correspondingly
OBJECTS  = $(patsubst $(KSRC_DIR)/%.S, $(BUILD_DIR)/$(KSRC_DIR)/%_S.o, $(ASM_FILES))
OBJECTS += $(patsubst $(KSRC_DIR)/%.c, $(BUILD_DIR)/$(KSRC_DIR)/%.o, $(KSRC_FILES))
OBJECTS += $(patsubst $(CSRC_DIR)/%.c, $(BUILD_DIR)/$(CSRC_DIR)/%.o, $(CSRC_FILES))

# Assemble list of header files
HEADERS  = $(wildcard $(HEAD_DIR)/*.h)

# Default target (invoked by `make` or `make all`). Produces 'kernel8.img' which can then be booted from
all: kernel8.img

# All assembly source targets
$(BUILD_DIR)/$(KSRC_DIR)/%_S.o: $(KSRC_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# All kernel source targets
$(BUILD_DIR)/$(KSRC_DIR)/%.o: $(KSRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# All common source targets
$(BUILD_DIR)/$(CSRC_DIR)/%.o: $(CSRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# Remove kernel and build directory
clean:
	rm -rf $(BUILD_DIR) *.img

# Compile lists with the dependencies between objects
DEP_FILES = $(OBJECTS:%.o=%.d)
	-include $(DEP_FILES)

# Actual kernel building target
kernel8.img: $(SRC_DIR)/linker.ld $(OBJECTS)
	echo $(OBJECTS)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJECTS)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
