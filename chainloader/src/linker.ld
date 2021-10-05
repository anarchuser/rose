LOAD_ADDR = 0x80000;

SECTIONS
{
    . = LOAD_ADDR - 4096;
    PROVIDE(_code = .);
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) }
	bss_end = .;
	_end = .;
}