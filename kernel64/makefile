NASM64 = nasm -f elf64
GCC64 = x86_64-elf-gcc -c -m64 -ffreestanding
LD64 = x86_64-elf-ld -melf_x86_64 -T ../elf_x86_64.x -nostdlib -e main -Ttext 0x200000
OBJCOPY64 = x86_64-elf-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECTDIRECTORY = tmp
SOURCEDIRECTORY = src

all: prepare kernel64.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)

dep:
	@echo === Make Dependency File ===
	make -C $(OBJECTDIRECTORY) -f ../makefile internal-dependency
	@echo === Dependency Search Complete ===

execute-internal-build: dep
	make -C $(OBJECTDIRECTORY) -f ../makefile kernel64.elf

kernel64.bin: execute-internal-build
	$(OBJCOPY64) $(OBJECTDIRECTORY)/kernel64.elf $@

clean:
	rm -f *.bin
	rm -f $(OBJECTDIRECTORY)/*.*

ENTRYPOINTSOURCEFILE = ../$(SOURCEDIRECTORY)/entrypoint.s
ENTRYPOINTOBJECTFILE = entrypoint.o

CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.c)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(notdir $(patsubst %.c, %.o, $(CSOURCEFILES)))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLYSOURCEFILES)))

$(ENTRYPOINTOBJECTFILE): $(ENTRYPOINTSOURCEFILE)
	$(NASM64) -o $@ $<

%.o: ../$(SOURCEDIRECTORY)/%.c
	$(GCC64) -c $<

%.o: ../$(SOURCEDIRECTORY)/%.asm
	$(NASM64) -f elf64 $< -o $@

internal-dependency:
	$(GCC64) -MM $(CSOURCEFILES) > dependency.dep

kernel64.elf: $(ENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	$(LD64) -o $@ $^

ifeq (dependency.dep, $(wildcard dependency.dep))
include dependency.dep
endif
