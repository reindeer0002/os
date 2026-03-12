/* Set target format to 32-bit i386 ELF */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)

/* Set the Entry Point: Execution starts at the _start symbol */
ENTRY(_start)

SECTIONS
{
    /* Set the kernel starting address to 0x10200 */
    . = 0x10200;

    /* .text */
    .text :
    {
        *(.text .stub .text.* .gnu.linkonce.t.*)
        *(.gnu.warning)
    } = 0x90909090  /* Fill padding space with NOP (0x90) instructions */

    /* .rodata */
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) }

    /* Section alignment (512-byte boundary) */
    /* Align the address to make it easier for the bootloader to read disk sectors (512 bytes). */
    . = ALIGN(512);

    /* .data */
    .data :
    {
        *(.data .data.* .gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
    }

    /* .bss */
    __bss_start = .;
    .bss :
    {
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4); /* 4-byte alignment */
    }
    _end = .;
    PROVIDE (end = .);

    /* Discard unnecessary sections */
    /DISCARD/ :
    {
        *(.note.GNU-stack)
        *(.comment)
        *(.eh_frame) /* Remove exception handling frames if not required */
    }
}