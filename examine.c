#include <stdio.h>
#include <stdlib.h>

int examine(void *data, const int count, const int blocksize, const char format){
	
	int i,j;
	void **addresses;
	char **binStrings;
	char *fmt;

	char *binValue = 	"%s";
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
	
	
	
	// Checking arguments 
	if (data == NULL) return 1;
	
	if (blocksize != sizeof(char) && blocksize != sizeof(short) &&
		blocksize != sizeof(int)  && blocksize != sizeof(long)) return 2;
	
	if (format == 'c' && blocksize != sizeof(char) ) return 2;
	
	if (format != 'd' && format != 'u' && format != 'o' && 
		format != 'b' && format != 'c' && format != 'x') return 3;
		
	
	// Mallocating space
	addresses = malloc(count * sizeof(void*));
	binStrings = malloc(count * sizeof(void*));
	for (i = 0; i < count; i++)
		binStrings[i] = malloc((blocksize*8)+1);
	
	
	
	// Setting appropriate format-string
	// Storing addresses of data that will be examined
	switch(blocksize){
		case sizeof(char):
			for (i = 0; i < count; i++) addresses[i] = ((char*)data)+i;
			switch(format){
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
				case 'b':
					fmt = binValue;
					for (i = 0; i < count; i++)
						for (j = 7; j >= 0; j--, *(((unsigned char*) data) + i) /= 2)
							binStrings[i][j] = ( *(((unsigned char*) data) + i) %  2) + '0';
					break;
			} break;

		case sizeof(short):
			for (i = 0; i < count; i++) addresses[i] = ((short*)data)+i;
			switch(format){
				case 'x':
					fmt = hexWord; break;
				case 'd':
					fmt = decWord; break;
				case 'u':
					fmt = udecWord; break;
				case 'o':
					fmt = octWord; break;	
				case 'b':
					fmt = binValue;
					for (i = 0; i < count; i++)
						for (j = 15; j >= 0; j--, *(((unsigned short*) data) + i) /= 2)
							binStrings[i][j] = ( *(((unsigned short*) data) + i) %  2) + '0';
					break;
			} break;
		
		case sizeof(int):
			for (i = 0; i < count; i++) addresses[i] = ((int*)data)+i;
			switch(format){
				case 'x':
					fmt = hexDword; break;
				case 'd':
					fmt = decDword; break;
				case 'u':
					fmt = udecDword; break;
				case 'o':
					fmt = octDword; break;
				case 'b':
					fmt = binValue;
					for (i = 0; i < count; i++)
						for (j = 31; j >= 0; j--, *(((unsigned int*) data) + i) /= 2)
							binStrings[i][j] = ( *(((unsigned int*) data) + i) %  2) + '0';
					break;
			} break;
		
		case sizeof(long):
			for (i = 0; i < count; i++) addresses[i] = ((long*)data)+i;
			switch(format){
				case 'x':
					fmt = hexQword; break;
				case 'd':
					fmt = decQword; break;
				case 'u':
					fmt = udecQword; break;
				case 'o':
					fmt = octQword; break;
				case 'b':
					fmt = binValue;
					for (i = 0; i < count; i++)
						for (j = 63; j >= 0; j--, *(((unsigned long*) data) + i) /= 2)
							binStrings[i][j] = ( *(((unsigned long*) data) + i) %  2) + '0';
					break;
			} break;
							
	}
	
	
	
	// Print loop
	for (i = 0; i < count; i++){
		
		// For formatting reasons
		if (i%2 == 0)
			(i != 0) ? printf("\n%p:\t",addresses[i]) : printf("%p:\t",addresses[i]);
	
		// If format is binary, then print the strings stored in `binStrings`
		// else, print values pointed by the addresses stored in `addresses`
		(format != 'b') ? printf(fmt,**((long**)addresses+i)) : printf(fmt,binStrings[i]);
		printf("\t");
	}	
	
	
	
	// Deallocate space
	for (i = 0; i < count; i++)
		free(binStrings[i]);
	free(binStrings);
	free(addresses);
	return 0;

}
