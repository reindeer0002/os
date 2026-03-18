.PHONY: boot-loader kernel32 kernel64 disk.img # utility

all: boot-loader kernel32 kernel64 disk.img # utility

boot-loader:
	@echo
	@echo ============== Build Boot Loader ==============
	@echo

	make -C boot-loader

	@echo
	@echo ============== Build Complete ==============
	@echo

kernel32:
	@echo
	@echo ============== Build 32bit Kernel ==============
	@echo

	make -C kernel32

	@echo
	@echo ============== Build Complete ==============
	@echo

kernel64:
	@echo
	@echo ============== Build 64bit Kernel ==============
	@echo

	make -C kernel64

	@echo
	@echo ============== Build Complete ==============
	@echo

disk.img: boot-loader/boot-loader.bin kernel32/kernel32.bin kernel64/kernel64.bin
	@echo
	@echo ============== Disk Image Build Start ==============
	@echo

	./image-maker $^

	@echo
	@echo ============== All Build Complete ==============
	@echo

# utility:
# 	@echo
# 	@echo ============== Utility Build Start ==============
# 	@echo

# 	make -C utility

# 	@echo
# 	@echo ============== Utility Build Complete ==============
# 	@echo

clean:
	make -C boot-loader clean
	make -C kernel32 clean
	make -C kernel64 clean
	make -C utility clean
	rm -f disk.img
