/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "uart.h"
#include "circbuf.h"
#include "logger.h"

static int i = 0;

CircBuf_t *Tx_Buf;
CircBuf_t *Rx_Buf;

void UART0_IRQHandler()
{
	__disable_irq();
	uint8_t c;
	if((UART0->C2 & UART0_C2_TIE_MASK) == UART0_C2_TIE_MASK)
	{
		if(Tx_Buf->num_items > 0)
		{
			circbuf_remove(Tx_Buf, &c);
			uart_send_byte(c);
		}
		else
		{
//			UART0->C2 &= ~UART0_C2_TCIE_MASK;
			UART0->C2 &= ~UART0_C2_TIE_MASK;
			Tx_Buf->send_status = 0;
		}
	}
	else if((UART0->C2 & UART0_C2_RIE_MASK) == UART0_C2_RIE_MASK)
	{
		if(Rx_Buf->num_items < Rx_Buf->size)
		{
			uart_receive_byte(&c);
			uart_send_byte(c);
			circbuf_add(Rx_Buf, c);
		}
		else
		{
//			UART0->C2 &= ~UART0_C2_TCIE_MASK;
			UART0->C2 &= ~UART0_C2_RIE_MASK;
//			Tx_Buf->send_status = 0;
		}

	}
	else
		return;
	__enable_irq();
}


int main(void)
{
	uart_configure();

//	uart_send_byte(0xaa);

	Tx_Buf = (CircBuf_t *)malloc(sizeof(CircBuf_t));
	int8_t res = circbuf_init(Tx_Buf, 100);

	Rx_Buf = (CircBuf_t *)malloc(sizeof(CircBuf_t));
	res = circbuf_init(Rx_Buf, 100);

	uint8_t string[] = "Free Rick 2017 ";

	LogItem_t *testing;
	testing = (LogItem_t *)malloc(sizeof(LogItem_t));
	create_log_item(testing, 1, sizeof(string), string);

	log_item(Tx_Buf, testing);

    while(1)
    {
    	for (uint32_t a = 0;a < 1280000; a++)
    	{
			;
		}
    	log_item(Tx_Buf, testing);
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
