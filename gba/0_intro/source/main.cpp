int main() {
    //*(unsigned short*)0x04000000 = 0x403;
    //*(unsigned short*)0x060000A0 = 0xAFF;
    //*(unsigned short*)0x0600A0A0 = 0xAFF;
    asm(
        "ldr r0, #0x04000000\n"
        "ldr r1, =#0x403\n"
        "strh r1, [r0]\n"
        "ldr r0, =#0x6000000\n"
        "ldr r1, =#0x1EF\n"
        "strh r1, [r0]\n"
        "ldr r0, =#0x600A0A0\n"
        "strh r1, [r0]\n"
        ::: "r0", "r1"
    );
    return 0;
}
