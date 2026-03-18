/* Default linker script for 64-bit kernel executables */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

SECTIONS
{
    /* 1. Set the base address to 0x200000 (2MB) for 64-bit mode */
    . = 0x200000;

    /* 2. Relocate essential sections to the front for easier loading */
    .text :
    {
        /* Include the executable headers and all text sections */
        *(.text .stub .text.* .gnu.linkonce.t.*)
        /* Handle special GNU warning sections */
        *(.gnu.warning)
    } =0x90909090  /* Fill gaps with NOP instructions (0x90) */

    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
    .rodata1 : { *(.rodata1) }

    /* 3. Align the start of the data section to a 512-byte sector boundary */
    /* This simplifies debugging and disk I/O operations */
    . = ALIGN(512); 
    
    .data :
    {
        *(.data .data.* .gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
    }
    .data1 : { *(.data1) }

    _edata = .;
    PROVIDE (edata = .);

    /* 4. Define the BSS section for uninitialized global variables */
    __bss_start = .;
    .bss :
    {
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        /* Align to 8 bytes (64-bit) for CPU performance optimization */
        . = ALIGN(. != 0 ? 64 / 8 : 1);
    }

    /* Define the end of the memory image */
    _end = .;
    PROVIDE (end = .);

    /* 5. Discard unnecessary sections to keep the binary clean */
    /DISCARD/ :
    {
        *(.note.GNU-stack)
        *(.comment)
        *(.eh_frame)
    }
}