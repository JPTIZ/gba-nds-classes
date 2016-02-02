int main() {
	//*(unsigned short*)0x04000000 = 0x403;
	//*(unsigned short*)0x060000A0 = 0xAFF;
	//*(unsigned short*)0x0600A0A0 = 0xAFF;
		asm(
			"mov r0, #0x04000000\n"
			"ldr r1, =#0x403\n"
			"strh r1, [r0]\n" :::
		);
	auto ban = 0u;
	while (1) {
		((unsigned short*)0x060000A0)[30*240 + 18] = (31 << ban-4);
		ban = (ban + 1) % 15;
	}
	return 0;
}
