MEMORY
{
    flash   (rx)    : ORIGIN = 0x00000000, LENGTH = 0x00080000
    ram     (rxw)   : ORIGIN = 0x20000000, LENGTH = 0x00010000
}

STACK_SIZE = 0x400;
__ram_end = ORIGIN(ram) + LENGTH(ram);

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        *(.text);
    } > flash

    .rodata :
    {
        __srodata = .;
        *(.rodata);
        __erodata = .;
    } > flash

    .bss (NOLOAD) :
    {
        __sbss = .;
        *(.bss);
        *(.bss*);
        __ebss = .;
    } > ram

    .data : AT (__erodata)
    {
        __sdata = .;
        *(.data);
        __edata = .;
    } > ram

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __sstack = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        __estack = .;
    }
}
