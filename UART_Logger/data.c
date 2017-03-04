#include <stdio.h>
#include <stdint.h>
#include "data.h"

#ifdef KL25Z_PLATFORM
#define printf(...)
#endif

// #define  big_to_little
#define B0 0X000000FF 
#define B1 0X0000FF00
#define B2 0X00FF0000
#define B3 0XFF000000
#define three_bytes 24
#define one_byte 8
#define ZERO 0x30


int8_t *reverse(int8_t *src, uint32_t length)
{
	/*Checking for special conditions*/
	if(src==NULL||length<=0)
		return src;
	if(length==1)
		return src;
	int8_t temp;//temporary variable to swap bytes
	int8_t *ptr=src;
	ptr=ptr+(length-1);//Make ptr point to the end of the array
	int8_t i=0;
	for(i=0;i<length/2; i++)
	{
	    temp= *(src+i);
	    *(src+i)=*ptr;
	    *ptr=temp;
	     ptr--;
	}
		return src;
}


uint8_t *my_itoa(uint8_t *str, int32_t data, int32_t base)
{
	uint8_t negative=0;
	int8_t i=0;
	uint8_t rem;
	/*Handle negative data by setting a flag and making the number positive so that it can be made negative at the end */
	if(data<0)
	{
		negative=1;
		data=-(data);
	}
	/*If the number is a zero then just return a null terminated zero*/
	if(data==0)
	{
		*(str+i)='0';
		i++;
		*(str+i)='\0';
		return str;
	}
	while(data!=0)
	{
		/*Calculate the remainder to extract the least significant digit*/
		rem=data%base;
		if(rem<=9)
			{
				*(str+i)=(uint8_t)(rem+'0');
				i++;
			}
		else
			{
				*(str+i)=(uint8_t)((rem-10) + 'a');
				i++;
			}
		data=data/base;
	}	
	if(negative==0)
	{
		/*Reverse the result since digits were picked from the LSB end*/
		reverse(str,i);
		/*Add a null terminator*/
			*(str+i)='\0';
		return str;
	}
	else
	{
		/*Add a negative sign to denote the result is negative*/
		 *(str+i)='-';
		 i++;
		 /*Reverse the result since digits were picked from the LSB end*/
		 reverse(str,i);
		 /*Add a null terminator*/
		 *(str+i)='\0';
		 return str;
	}	

}


int32_t my_atoi(int8_t *str)
{
	uint8_t negative=0;
	uint32_t result=0;
	int32_t i=0;
	if(*(str+i)=='-')
	{
		negative=1;
		i++;
	}	
	/*Loop until it reaches the end of the string*/
	while(*(str+i)!='\0')
	{
		result=result*10 + (((*(str+i)-ZERO) > 9) ? (0):(*(str+i)-ZERO));
		i++;
	}
	if(negative==1)
	{
		result=-result;
	}
	return result;
}


int8_t big_to_little(uint32_t *data, uint32_t length)
{
	if(data==NULL)
		return 1;
	uint8_t i=0;
	uint32_t bit0, bit1, bit2, bit3;
	for (i = 0; i < length; i++)
	{
		/*Zero out the other bits apart from the 0th byte and shift it three bytes to the left*/
		bit0 = (*(data+i)&B0)<<three_bytes;
		/*Zero out the other bits apart from the 1st byte and shift it one byte to the left*/
		bit1 = (*(data+i)&B1)<<one_byte;
		/*Zero out the other bits apart from the 2nd byte and shift it one byte to the right*/
		bit2 = (*(data+i)&B2)>>one_byte;
		/*Zero out the other bits apart from the 3rd byte and shift it three bytes to the right*/
		bit3 = (*(data+i)&B3)>>three_bytes;
		/*Combine all the bytes together by ORing them together*/
		*(data+i) = bit3|bit2|bit1|bit0;
	}
	return 0;
}

int8_t little_to_big(uint32_t *data, uint32_t length)
{
	if(data==NULL)
		return 1;
	uint8_t i=0;
	uint32_t bit0, bit1, bit2, bit3;
	for (i = 0; i < length; i++)
	{
		/*Zero out the other bits apart from the 0th byte and shift it three bytes to the left*/
		bit0 = (*(data+i)&B0)<<three_bytes;
		/*Zero out the other bits apart from the 1st byte and shift it one byte to the left*/
		bit1 = (*(data+i)&B1)<<one_byte;
		/*Zero out the other bits apart from the 2nd byte and shift it one byte to the right*/
		bit2 = (*(data+i)&B2)>>one_byte;
		/*Zero out the other bits apart from the 3rd byte and shift it three bytes to the right*/
		bit3 = (*(data+i)&B3)>>three_bytes;
		/*Combine all the bytes together by ORing them together*/
		*(data+i) = bit3|bit2|bit1|bit0;
	}
	return 0;
}


void print_memory(uint8_t *start, uint32_t length)
{
	int8_t i=0;
	printf("\n");
	for (i = 0; i < length; i++)
	{
		printf("%x ",*(start+i));
	}
}
