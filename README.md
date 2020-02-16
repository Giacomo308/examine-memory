# examine-memory

##### This file is written in man-pages like style, just to explain everything more clearly.


### NAME  
	examine - examine memory at a certain address in gdb like style 


### SYNOPSIS  
	void examine(void *data, const int count, const int blocksize, const char format);  

### DESCRIPTION  
	The examine() function will help you to examine the memory like the "x" command in gdb.  
	data        is the pointer to the data block that you want to examine.  

	count       is the number of data blocks that you want to examine consecutively.  
	            It can be whatever integer number (be careful to read out of the segment).  
	blocksize	is the size, in byte, of the data block.  
	            It can be equal to 1,2,4 or 8.  
	format  	is the format of the output that you want to visualize the data block.  
			    It can be equal to 'd'(signed decimal), 'u'(unsigned decimal), 'x'(hexadecimal),
		    	'b'(binary), 'o'(octal), 'c'(ascii char).   
	
### EXAMPLE  
	To print an int value in its four bytes, in binary format:
		int a = 0xAABBCCDD;  
		examine((void*) &a, 4, sizeof(char), 'b'); 
	The output:
        0000005E2F3AF740:       11011101
        0000005E2F3AF741:       11001100
        0000005E2F3AF742:       10111011
        0000005E2F3AF743:       10101010		

