    .globl add_asm
add_asm:
    add w0, w1, w0
    add w0, w0, #100
    add w0, w0, w0
    ret