SECTIONS
{
    . = 0x80000;
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
    PROVIDE(_data = .);
	.data : { *(.data) }
	.bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }
    . = ALIGN(4096);
    _end = .;
}
__bss_size = (__bss_end - __bss_start) >> 3;