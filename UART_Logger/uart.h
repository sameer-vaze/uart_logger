/*
 * uart.h
 *
 *  Created on: Feb 23, 2017
 *      Author: sameer
 */

#include <stdlib.h>
#include <stdint.h>
#include "MKL25Z4.h"

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

/*********************************************************************
*uart_configure
*	description:This function initializes the UART0 for the KL25Z and
*	sets the values of the configuration registers in order to get the
*	following characteristics:
*		1. Baud Rate: 38400
*		2. 8 bit data
*		3. Single stop bit
*		4. Sets up the UART pins
*		5. Enables transmit and receive
*	parameters:N/A

*	returns:N/A
*********************************************************************/

void uart_configure();

/*********************************************************************
*uart_send_byte
*	description:This function writes to the data register of the UART0
*	so that the it can be shifted out and sent to the destination for
*	the logger that is to be implemented.
*	parameters:
*		uint8_t data: The single byte of data that is to be transmitted
*		across the UART
*
*	returns:N/A
*********************************************************************/

void uart_send_byte(uint8_t data);

/*********************************************************************
*uart_send_byte_n
*	description:This function writes n bytes to the data register of
*	the UART0 so that the it can be shifted out and sent to the
*	destination for the logger that is to be implemented.
*	parameters:
*		uint8_t *data_ptr: The pointer to length bytes of data that is
*		to be transmitted across the UART
*
*		size_t length: The length in bytes
*
*	returns:N/A
*********************************************************************/

void uart_send_byte_n(uint8_t *data_ptr, size_t length);

/*********************************************************************
*uart_receive_byte
*	description:This function reads from the data register of the UART
*	so that the it can be used by the program.
*	parameters:
*		uint8_t *data_ptr: Pointer to a variable/memory location that
*		will store the value of the received byte
*
*	returns:N/A
*********************************************************************/

void uart_receive_byte(uint8_t *data_ptr);

#endif
