AS = ~/opt/cross/bin/i386-elf-as
CC = ~/opt/cross/bin/i386-elf-gcc

BUILD_DIR = ./build
SRC_DIR = ./src
INC_DIR = ./src
BIN_DIR = ./bin
TARGET = simple_os.bin

CCFLAGS := -c -std=gnu99 -ffreestanding -g -O2 -Wall -Wextra -I$(INC_DIR)
LDFLAGS := -ffreestanding -O2 -nostdlib

SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)


$(BIN_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -T linker.ld -o $@ $(LDFLAGS) $(OBJS) -lgcc

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@) 
	$(CC) $(CCFLAGS) $< -o $@


.PHONY: run clean
run:
	@ qemu-system-i386 -kernel $(BIN_DIR)/$(TARGET)

clean: 
	@ rm -r build bin
