.thumb
.align 2
.globl main
.thumb_func

main:
    ldr r0, =0x04000000
    ldr r1, =0x403
    strh r1, [r0]
    ldr r0, =0x6000000
    ldr r1, =0x1EF
    strh r1, [r0]
    ldr r0, =0x6000f08
    strh r1, [r0]
    b infin

infin:
    b infin
