all: os.img

os.img: bootsector.bin mykernel.bin
	cat $^ > os.img

bootsector.bin: 32bit-main.asm 32bit-switch.asm
	nasm $< -f bin -o $@

mykernel.bin: mykernel_entry.o mykernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 --oformat binary $^

mykernel_entry.o: mykernel_entry.asm
	nasm $< -f elf -o $@

mykernel.o: mykernel.c mykernel.h
	i386-elf-gcc -ffreestanding -c $< -o $@

run: os.img
	qemu-system-x86_64 $<

clean:
	rm -f *.o *.bin *.img *.dis
