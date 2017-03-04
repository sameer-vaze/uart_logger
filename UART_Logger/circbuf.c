#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"

CB_Enum_t circbuf_init(CircBuf_t *circ, size_t size_of_buffer)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}

	circ->size = size_of_buffer;
	circ->buffer = (uint8_t *)malloc(size_of_buffer);
	circ->head = circ->buffer;
	circ->tail = circ->buffer;
	circ->send_status = 0;
	circ->num_items = 0;

	if(circ->buffer == NULL)
	{
		return BUFFER_ALLOCATION_FAILED;
	}
	else
	{
		return NO_ERROR;	
	}
}

CB_Enum_t circbuf_add(CircBuf_t *circ, uint8_t data)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}
	else if(circ->num_items == circ->size)
	{
		return BUFFER_FULL;
	}

	if(circ->num_items == 0)
	{
		*circ->head = data;
		circ->num_items++;
		return NO_ERROR;
	}
	else
	{
		if((circ->head - circ->buffer) == circ->size - 1)
		{
			circ->head = circ->buffer;
			*(circ->head) = data;
			circ->num_items++;
		}
		else
		{
			circ->head++;
			*(circ->head) = data;
			circ->num_items++;
		}

		return NO_ERROR;
	}
}

CB_Enum_t circbuf_remove(CircBuf_t *circ, uint8_t *data_ptr)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}
	else if(circ->num_items == 0)
	{
		return BUFFER_EMPTY;
	}

	if(circ->num_items == 1)
	{
		*data_ptr = *(circ->tail);
		circ->num_items--;
		return NO_ERROR;
	}
	else
	{
		if((circ->tail - circ->buffer) == circ->size - 1)
		{
			*data_ptr = *(circ->tail);
			circ->tail = circ->buffer;
			circ->num_items--;
		}
		else
		{
			*data_ptr = *(circ->tail);
			circ->tail++;
			circ->num_items--;
		}
		return NO_ERROR;
	}	
}

CB_Enum_t circbuf_full(CircBuf_t *circ)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}

	if(circ->num_items == circ->size)
	{
		return BUFFER_FULL;
	}
	else
	{
		return NO_ERROR;
	}
}

CB_Enum_t circbuf_empty(CircBuf_t *circ)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}

	if(circ->num_items == 0)
	{
		return BUFFER_EMPTY;
	}
	else
	{
		return NO_ERROR;
	}
}

CB_Enum_t circbuf_peek(CircBuf_t *circ, size_t index, uint8_t *data_ptr)
{
	if(circ == NULL)
	{
		return NULL_POINTER;
	}
	else if(index > circ->num_items)
	{
		return NO_LENGTH;
	}

	if((circ->tail + index) > (circ->buffer + circ->num_items))
	{
		index -= ((circ->buffer + circ->num_items) - (circ->tail) + 1);
		*(data_ptr) = *(circ->buffer + index);

	}
	else
	{
		*(data_ptr) = *(circ->tail + index);

	}

	return NO_ERROR;
}

/*int main()
{
	CircBuf_t *test;
	test = (CircBuf_t *)malloc(sizeof(CircBuf_t));
	int8_t res = circbuf_init(test, 10);
	printf("res is %d\n", res);
	for(uint8_t i = 0; i < 10; i++)
	{
		res = circbuf_add(test, i);
		printf("res is %d\n", res);
	}

	printf("Peek test starts here \n");

	uint8_t val;
	for (uint8_t j = 0; j < 10; j++)
	{
		res = circbuf_peek(test, j, &val);
		printf("res is %d\n", res);
		printf("val is %d\n", val);
	}
	printf("num_items is %lu\n", test->num_items);

	printf("++++++++++++++++++\n");
	
	res = circbuf_remove(test, &val);
	printf("res is %d\n", res);
	printf("val is %d\n", val);

	res = circbuf_remove(test, &val);
	printf("res is %d\n", res);
	printf("val is %d\n", val);

	res = circbuf_remove(test, &val);
	printf("res is %d\n", res);
	printf("val is %d\n", val);

	printf("num_items is %lu\n", test->num_items);

	res = circbuf_add(test, 22);
	printf("res is %d\n", res);

	res = circbuf_add(test, 33);
	printf("res is %d\n", res);

	printf("num_items is %lu\n", test->num_items);

	printf("++++++++++++++++++\n");


	for (uint8_t j = 0; j < 9; j++)
	{
		res = circbuf_peek(test, j, &val);
		printf("res is %d\n", res);
		printf("val is %d\n", val);
	}

	res = circbuf_add(test, 44);
	printf("res is %d\n", res);


	res = circbuf_add(test, 55);
	printf("res is %d\n", res);
}*/
