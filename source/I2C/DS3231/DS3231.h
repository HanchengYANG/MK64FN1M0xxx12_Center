/*
 * DS3231.h
 *
 *  Created on: 2017年4月21日
 *      Author: hanch
 */

#ifndef DS3231_DS3231_H_
#define DS3231_DS3231_H_

#include "fsl_common.h"

/*********             Public macro             *********/


/*********             Public types             *********/

typedef enum {
	DS_MOD_SEC = 0x01,
	DS_MOD_MIN = 0x02,
	DS_MOD_HOUR = 0x04,
	DS_MOD_DAY = 0x08,
	DS_MOD_DATE = 0x10,
	DS_MOD_MONTH = 0x20,
	DS_MOD_YEAR = 0x40
} DS_ConfigFlagType;

typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint16_t year;
} DS_DataStruct;

/*********            Public variables          *********/

/*********      Public function declaration     *********/

void DS_Init();

void DS_Set(DS_ConfigFlagType flag, DS_DataStruct* configPtr);

void DS_GetDateTime(DS_DataStruct* configPtr);

bool DS_GetTemp(float *temp);

#endif /* DS3231_DS3231_H_ */
