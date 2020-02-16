#include <stdio.h>
#include <stdint.h>


char *hexByte =		"%02hhx";
char *decByte =		"%03hhd";
char *udecByte =	"%03hhu";
char *octByte =		"%03hho";
char *asciiByte =	"%c";

char *hexWord =		"%04hx";
char *decWord =		"%05hd";
char *udecWord =	"%05hu";
char *octWord =		"%06ho";

char *hexDword =	"%08x";
char *decDword =	"%010d";
char *udecDword =	"%010u";
char *octDword =	"%011o";

char *hexQword =	"%016lx";
char *decQword =	"%020ld";
char *udecQword =	"%020lu";
char *octQword = 	"%022lo";

void bin(void *data, const int size)
{
	int i, j;
	unsigned char *ptr;
	ptr = (unsigned char*) data;

	for (i=size-1; i >= 0; i--)
		for (j=7; j >= 0; j--)
			printf("%u", (ptr[i] >> j) & 1);
}

void examine1(void *data, const int count, const char format)
{
	char *fmt;
	uint32_t i;
	int8_t *ptr = (int8_t*) data;


	switch(format){
		case 'b':
			break;
		case 'x':
			fmt = hexByte; break;
		case 'd':
			fmt = decByte; break;
		case 'u':
			fmt = udecByte; break;
		case 'o':
			fmt = octByte; break;
		case 'c':	
			fmt = asciiByte; break;
		default:
			return;
	}

	for(i=0; i<count; i++)
	{
		printf("%p:\t", ptr+i);
		
		if (format == 'b')
			bin(ptr+i, sizeof(int8_t));
		else
			printf(fmt, *(ptr+i));
		
		printf("\n");
	}

}

void examine2(void *data, const int count, const char format)
{
	char *fmt;
	uint32_t i;
	int16_t *ptr = (int16_t*) data;


	switch(format){
		case 'b':
			break;
		case 'x':
			fmt = hexWord; break;
		case 'd':
			fmt = decWord; break;
		case 'u':
			fmt = udecWord; break;
		case 'o':
			fmt = octWord; break;
		default:
			return;
	}

	for(i=0; i<count; i++)
	{
		printf("%p:\t", ptr+i);
		
		if (format == 'b')
			bin(ptr+i, sizeof(int16_t));
		else
			printf(fmt, *(ptr+i));
		
		printf("\n");
	}
}

void examine4(void *data, const int count, const char format)
{
	char *fmt;
	uint32_t i;
	int32_t *ptr = (int32_t*) data;


	switch(format){
		case 'b':
			break;
		case 'x':
			fmt = hexDword; break;
		case 'd':
			fmt = decDword; break;
		case 'u':
			fmt = udecDword; break;
		case 'o':
			fmt = octDword; break;
		default:
			return;
	}

	for(i=0; i<count; i++)
	{
		printf("%p:\t", ptr+i);
		
		if (format == 'b')
			bin(ptr+i, sizeof(int32_t));
		else
			printf(fmt, *(ptr+i));
		
		printf("\n");
	}

}

void examine8(void *data, const int count, const char format)
{
	char *fmt;
	uint32_t i;
	int64_t *ptr = (int64_t*) data;


	switch(format){
		case 'b':
			break;
		case 'x':
			fmt = hexQword; break;
		case 'd':
			fmt = decQword; break;
		case 'u':
			fmt = udecQword; break;
		case 'o':
			fmt = octQword; break;
		default:
			return;
	}

	for(i=0; i<count; i++)
	{
		printf("%p:\t", ptr+i);
		
		if (format == 'b')
			bin(ptr+i, sizeof(int64_t));
		else
			printf(fmt, *(ptr+i));
		
		printf("\n");
	}

}

void examine(void *data, const int count, const int blocksize, const char format)
{

	switch(blocksize){
		case sizeof(int8_t):
			examine1(data, count, format); break;

		case sizeof(int16_t):
			examine2(data, count, format); break;

		case sizeof(int32_t):
			examine4(data, count, format); break;

		case sizeof(int64_t):
			examine8(data, count, format); break;
	}

}