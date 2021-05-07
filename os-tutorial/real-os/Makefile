C_SOURCES = $(wildcard kernel/*.c drivers/*.c common/*.c cpu/x86/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h common/include/*.h cpu/x86/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -Wextra -Wall -Werror -g -Icommon/include -Idrivers

# First rule is run by default
os.img: boot/32bit-main.bin kernel.bin
	cat $^ > $@

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/mykernel_entry.o cpu/x86/igates.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/mykernel_entry.o cpu/x86/igates.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os.img
	qemu-system-i386 -fda os.img

# Open the connection to qemu and load our kernel-object file with symbols
debug: os.img kernel.elf
	qemu-system-i386 -s -S os.img &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os.img *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o common/*.o cpu/x86/*.o
