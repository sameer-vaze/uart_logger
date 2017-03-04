#ifndef DATA_H
#define DATA_H
#include <stdint.h>


/*List of function prototypes*/


/*********************************************************************
*reverse
*	description:Moves specified number of bytes from a source address
				to a destination address. The function handles 
				situations where the destination and source address
				ranges have overalapping regions.
*	parameters:
		int8_t *src - Pointer to the start of the source address
		uint32_t length - Number of bytes to be moved from source to
							destination
*	returns:
			Returns a pointer to the starting location of the reversed
			series of bytes
*********************************************************************/
int8_t *reverse(int8_t *src, uint32_t length);


/*********************************************************************
*my_itoa
*	description:Converts data from integer to ASCII format

*	parameters:
		int8_t *str - Pointer to the starting location of the converted
						data in ASCII format
		int32_t data - Integer value which is to be converted
		int32_t base - Base of the integer value
*	returns:
			Returns pointer to the converted ASCII data
*********************************************************************/
uint8_t *my_itoa(uint8_t *str, int32_t data, int32_t base);


/*********************************************************************
*my_atoi
*	description:Converts data from ASCII to integer format

*	parameters:
		int8_t *str - Pointer to the ASCII data
		
*	returns:
			Returns the converted integer value
*********************************************************************/
int32_t my_atoi(int8_t *str);


/*********************************************************************
*big_to_little
*	description:Converts data in memory from big endian to little
				endian
*	parameters:
		uint32_t *data - Pointer to the data which has to be converted
						from one endian to the other
		uint32_t length - Number of bytes upto which the conversion is
						to be done
		
*	returns:
			Returns the converted integer value
*********************************************************************/
int8_t big_to_little(uint32_t *data, uint32_t length);


/*********************************************************************
*little_to_big
*	description:Converts data in memory from little endian to big 
				endian
*	parameters:
		uint32_t *data - Pointer to the data which has to be converted
						from one endian to the other
		uint32_t length - Number of bytes upto which the conversion is
						to be done
		
*	returns:
			Returns the converted integer value
*********************************************************************/
int8_t little_to_big(uint32_t *data, uint32_t length);


/*********************************************************************
*print_memory
*	description:Prints the contents of memory upto a specified length

*	parameters:
		uint8_t *start - Pointer to the data which is to be printed
		uint32_t length - Number of bytes upto which the data is to
						  be printed
		
*	returns:
			N/A
*********************************************************************/
void print_memory(uint8_t *start, uint32_t length);


#endif
