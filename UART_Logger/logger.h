/*
 * logger.h
 *
 *  Created on: Feb 24, 2017
 *      Author: sameer
 */

#ifndef SOURCES_LOGGER_H_
#define SOURCES_LOGGER_H_


typedef enum LGe
{
	LOGGER_INITIALIZED = (uint32_t)0,
	GPIO_INITIALIZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMNERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYISIS_COMPLETED,
}LG_Enum_t;

typedef struct LogItem
{
	LG_Enum_t logID;
	size_t PLLength;
	uint8_t *PL;
}LogItem_t;

void log_data(CircBuf_t *circ, uint8_t *data_ptr, size_t length);

void log_string(CircBuf_t *circ, uint8_t *data_ptr);

void log_integer(CircBuf_t *circ, int32_t data);

void log_flush();

void create_log_item(LogItem_t *Item , LG_Enum_t ID, size_t length, uint8_t *payload);

void log_item(CircBuf_t *circ, LogItem_t *Item);

#endif
