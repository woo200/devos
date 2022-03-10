ifeq ($(shell uname),Linux)
	CC=gcc -mx32
	LD=ld -m elf_x86_64
else
	CC=x86_64-elf-gcc
	LD=x86_64-elf-ld
endif
AS=nasm

CCFLAGS=-ffreestanding -mno-red-zone -m64

KERNEL_SRCS = $(wildcard src/kernel/*.cpp)
KERNEL_SRCS += $(wildcard src/kernel/std/*.cpp)
KERNEL_SRCS += $(wildcard src/kernel/interrupts/*.cpp)
# KERNEL_SRCS += $(wildcard src/kernel/kstd/*.cpp)
# KERNEL_SRCS += $(wildcard src/os/std/*.cpp)
# KERNEL_SRCS += $(wildcard src/os/*.cpp)

KERNEL_OBJS=$(KERNEL_SRCS:.cpp=.o)

dirs:
	mkdir -p bin

all: run

doxygen:
	doxygen Doxyfile

kernel.bin: $(KERNEL_OBJS)
	$(LD) src/kernel/kernela.o $^ -T"link.ld"

kernel-entry.o:
	nasm src/kernel/kernel-entry.asm -f elf64 -o src/kernel/kernela.o

# gdt.o:
# 	$(CC) -Ttext 0x8000 -x c++ -c src/kernel/gdt.cpp16  -o bin/gdt.o -ffreestanding -mno-red-zone -m16

%.o: %.cpp
	$(CC) -Ttext 0x8000 -c $< -o $@ $(CCFLAGS)

binaries.o:
	nasm src/kernel/binaries.asm -f elf64 -o src/kernel/binaries.o

mbr.bin:
	nasm src/bootloader/bootloader.asm -f bin -o bin/mbr.bin

build: clean dirs mbr.bin kernel-entry.o kernel.bin 
	dd if=/dev/zero of=bin/image.bin bs=512 count=2880
	dd if=bin/mbr.bin of=bin/image.bin bs=512 conv=notrunc seek=0 count=1
	dd if=bin/kernel.bin of=bin/image.bin conv=notrunc seek=1 bs=512 count=2048

run: build
	qemu-system-x86_64 bin/image.bin -d int,cpu_reset -no-reboot

bochs: build
	bochs 'boot:floppy' 'floppya: 1_44=bin/image.bin, status=inserted'

clean:
	rm -f src/bootloader/*.o
	rm -f src/kernel/*.o
	rm -f src/kernel/std/*.o
	rm -f src/os/*.o
	rm -f src/os/std/*.o
	rm -f bin/*
