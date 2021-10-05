.globl put32
put32:
	str w1,[x0]
	ret

.globl get32
get32:
	ldr w0,[x0]
	ret

.globl delay
delay:
	subs x0, x0, #1
	bne delay
	ret

.global swap
swap:
    mov x25, x0
    mov x0, x20
    mov x20, x25

    mov x25, x1
    mov x1, x21
    mov x21, x25

    mov x25, x2
    mov x2, x22
    mov x22, x25

    mov x25, x3
    mov x3, x23
    mov x23, x25

    mov x25, x4
    mov x4, x24
    mov x24, x25

    ret
