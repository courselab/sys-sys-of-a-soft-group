.bits 16

movb $0xe, %ah

movb $'H', %al
int $0x10

movb $'e', %al
int $0x10

movb $'l', %al
int $0x10

movb $'l', %al
int $0x10

movb $'o', %al
int $0x10

movb $' ', %al
int $0x10

movb $'W', %al
int $0x10

movb $'o', %al
int $0x10

movb $'r', %al
int $0x10

movb $'l', %al
int $0x10

movb $'d', %al
int $0x10

halt:
    hlt
    jmp halt

.fill 510 - (. - _start), 1, 0
.word 0xaa55
