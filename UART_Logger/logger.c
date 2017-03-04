/*
 * logger.c
 *
 *  Created on: Feb 24, 2017
 *      Author: sameer
 */
#include <stdint.h>

#include "data.h"
#include "uart.h"
#include "circbuf.h"
#include "logger.h"

#define BASE_10	10
#define CIRC_USE_WITH_INT


#ifdef CIRC_USE

void log_data(CircBuf_t *circ, size_t length)
{
	while(length)
	{
		uint8_t c;
		circbuf_remove(circ, &c);
		uart_send_byte(c);
		length--;
	}
}

void log_string(CircBuf_t *circ)
{
	while(*(circ->tail) != '\0')
	{
		uint8_t c;
		circbuf_remove(circ, &c);
		uart_send_byte(c);
		data_ptr++;
	}
}

void log_flush(CircBuf_t *circ)
{
	while(circ->num_items != 0);
}

#endif

#ifdef CIRC_USE_WITH_INT

void log_data(CircBuf_t *circ, uint8_t *data_ptr, size_t length)
{
	while(length)
	{
		circbuf_add(circ, *data_ptr);
//		uart_send_byte(c);
		length--;
		data_ptr++;
	}
	circ->send_status = 1;
	if(circ->send_status == 1)
	{
		//Placeholder for software call for SWI
		UART0->C2 |= UART0_C2_TIE_MASK;
//		UART0_IRQHandler();
	}
}

void log_string(CircBuf_t *circ, uint8_t *data_ptr)
{
	while(*(circ->tail) != '\0')
	{
		circbuf_add(circ, *data_ptr);
//		uart_send_byte(c);
		data_ptr++;
	}
	circ->send_status = 1;
	if(circ->send_status == 1)
	{
		//Placeholder for software call for SWI
		UART0->C2 |= UART0_C2_TCIE_MASK;
//		UART0_IRQHandler();
	}
}

void log_integer(CircBuf_t *circ, int32_t data)
{
	uint8_t *data_ptr = (uint8_t *)malloc(11);
	data_ptr = my_itoa(data_ptr, data, BASE_10);
	while(*data_ptr != '\0')
	{
		circbuf_add(circ, *data_ptr);
//		uart_send_byte(*data_ptr);
		data_ptr++;
	}
	circ->send_status = 1;
	{
		//Placeholder for software call for SWI
		UART0->C2 |= UART0_C2_TCIE_MASK;
	}
}

#endif

#ifdef WITHOUT_CIRC

void log_data(uint8_t *data_ptr, size_t length)
{
	uart_send_byte_n(data_ptr, length);
}

void log_string(uint8_t *data_ptr)
{
	while(*data_ptr != '\0')
	{
		uart_send_byte(*data_ptr);
		data_ptr++;
	}
}

void log_integer(int32_t data)
{
	int8_t *data_ptr = my_itoa(data_ptr, data, BASE_10);
	while(*data_ptr != '\0')
	{
		uart_send_byte(*data_ptr);
		data_ptr++;
	}
}

void log_flush()
{

}
#endif

void create_log_item(LogItem_t *Item , LG_Enum_t ID, size_t length, uint8_t *payload)
{
	/*if(Item == NULL)
	{
		return NULL_POINTER;
	}*/

	Item->logID = ID;
	Item->PLLength = length;
	Item->PL = (uint8_t *)malloc(length);

	uint32_t i = length;

	while(i != 0)
	{
		*(Item->PL + length - i) = *(payload + length - i);
		i--;
	}

	/*if(Item->payload == NULL)
	{
		return BUFFER_ALLOCATION_FAILED;
	}
	else
	{
		return NO_ERROR;
	}*/
}


void log_item(CircBuf_t *circ, LogItem_t *Item)
{
	uint8_t ID_indicator[] = "LOG ID: ", PL_indicator[] = "Payload: ";
//	log_data(circ, ID_indicator, 8);
//	log_integer(circ, (int32_t)Item->logID);


	if(Item->PLLength != 0)
	{
//		log_data(circ, PL_indicator, 9);
		log_data(circ, (Item->PL), Item->PLLength);
	}
}
