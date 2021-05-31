/* endian.c (conforms to C89/90 standards) */
/* use valgrind to test for memory leaks/performance issue/code bottlenecks etc.. */
#include <stdio.h>

void test_endian();
unsigned short cpu_endian_test();
unsigned short cpu_endian(const int); /* supply custom address as argument */

unsigned short cpu_endian(const int addr)
{
	return 0;
}

/* 2 Bytes return value (16bit register), for readability; return value: 0 => big, 1 => little endian */
unsigned short cpu_endian_test()
{
	const int addr = 0x12345678;
	unsigned char *msb = (unsigned char*)&addr;
	return (*msb == 0x12) ? 0 : 1;
}

void test_endian()
{
	const int addr = 0x12345678;
	unsigned char *msb = (unsigned char*)&addr;
	register char *msb_msg = "big endian";
	register char *lsb_msg = "little endian";
	char *ptr = NULL;
	
	/*
		* little endian LSB => MSB
		* big endian MSB => LSB
		* ex: 0x123456 (big endian)
		* little endian => 0x563412
		*
		* data transfered over network => big endian
		* intel arch => little endian
		*
	*/
	
	(*msb == 0x12) ? (ptr = msb_msg) : (ptr = lsb_msg);
	printf("%s\n", ptr);
}

int main(int argc, char **argv)
{
	printf("ELF: %s contains %d arguments.\n", argv[0], argc);
	test_endian();
	
	if(cpu_endian_test())
	{
		printf("%s\n", "Detected big endian CPU");
	} else {
		printf("%s\n", "Detected little endian CPU");
	}
	return 0;
}

/* endian.c Makefile
GCC=gcc
LFLAGS=-O2
CFLAGS=-ansi -pedantic -Wall -Wextra

endian: endian.o
	$(GCC) $(CFLAGS) $(LFLAGS) endian.c -o endian
clean:
	rm ./*.o

EOF endian.c */
