/*
 * DS3231.c
 *
 *  Created on: 20170421
 *      Author: hanch
 */

#include "DS3231.h"
#include "I2C/HAL/I2C_HAL.h"

/*********             Internal macro             *********/
#define         DS3231_ADDR             0x68

#define         DS_SEC                  0x00
#define         DS_MIN                  0x01
#define         DS_HOUR                 0x02
#define         DS_DAY                  0x03
#define         DS_DATE                 0x04
#define         DS_MON_CEN              0x05
#define         DS_YEAR                 0x06
#define         DS_ALARM1_SEC           0x07
#define         DS_ALARM1_MIN           0x08
#define         DS_ALARM1_HOUR          0x09
#define         DS_ALARM1_DAY_DATE      0x0A
#define         DS_ALARM2_MIN           0x0B
#define         DS_ALARM2_HOUR          0x0C
#define         DS_ALARM2_DAY_DATE      0x0D
#define         DS_CONTROL              0x0E
#define         DS_CTRL_STAT            0x0F
#define         DS_AGING_OFFSET         0x10
#define         DS_TEMP_MSB             0x11
#define         DS_TEMP_LSB             0x12

#define			BIT0					0x01
#define			BIT1					0x02
#define			BIT2					0x04
#define			BIT3					0x08
#define			BIT4					0x10
#define			BIT5					0x20
#define			BIT6					0x40
#define			BIT7					0x80

/*********             Internal types             *********/

/*********            Internal variables          *********/

/*********      Internal function declaration     *********/

static void DS_ApplyConfig(DS_DataStruct* configPtr);

static bool DS_IsBusy();

/*********     Internal function implementation   *********/

static void DS_ApplyConfig(DS_DataStruct* configPtr) {
	static uint8_t config[8] = { DS_SEC };
	config[1] = ((configPtr->sec / 10) << 4) | (configPtr->sec % 10);
	config[2] = ((configPtr->min / 10) << 4) | (configPtr->min % 10);
	config[3] = ((configPtr->hour >= 20) << 5)
			| ((configPtr->hour >= 10 && configPtr->hour < 20) << 4)
			| (configPtr->hour % 10);
	config[4] = (configPtr->day & 0x07);
	config[5] = ((configPtr->date / 10) << 4) | (configPtr->date % 10);
	config[6] = ((configPtr->month >= 10) << 4) | (configPtr->month % 10);
	config[7] = (((configPtr->year - 2000) / 10) << 4)
			| ((configPtr->year - 2000) % 10);
	I2C_Write(DS3231_ADDR, config, sizeof(config));
}

static bool DS_IsBusy() {
	static uint8_t CtrlStat;
	I2C_Read(DS3231_ADDR, DS_CTRL_STAT, &CtrlStat, 1U);
	return (CtrlStat & 0x04 == 0x04);
}

/*********      Public function implementation    *********/

void DS_Init() {
	I2C_Init();
}

void DS_Set(DS_ConfigFlagType flag, DS_DataStruct* configPtr) {
	static DS_DataStruct oldConfig;
	DS_GetDateTime(&oldConfig);
	if (flag & DS_MOD_SEC) {
		oldConfig.sec = configPtr->sec;
	}
	if (flag & DS_MOD_MIN) {
		oldConfig.min = configPtr->min;
	}
	if (flag & DS_MOD_HOUR) {
		oldConfig.hour = configPtr->hour;
	}
	if (flag & DS_MOD_DAY) {
		oldConfig.day = configPtr->day;
	}
	if (flag & DS_MOD_DATE) {
		oldConfig.date = configPtr->date;
	}
	if (flag & DS_MOD_MONTH) {
		oldConfig.month = configPtr->month;
	}
	if (flag & DS_MOD_YEAR) {
		oldConfig.year = configPtr->year;
	}
	DS_ApplyConfig(&oldConfig);
}

void DS_GetDateTime(DS_DataStruct* configPtr) {
	static uint8_t result[7];
	I2C_Read(DS3231_ADDR, DS_SEC, result, sizeof(result));
	configPtr->sec = (result[0] & 0x0F) + ((result[0] & 0x70) >> 4) * 10;
	configPtr->min = (result[1] & 0x0F) + ((result[1] & 0x70) >> 4) * 10;
	configPtr->hour = ((result[2] & BIT5) == BIT5) * 20
			+ ((result[2] & BIT4) == BIT4) * 10 + (result[2] & 0x0F);
	configPtr->day = (result[3] & 0x07);
	configPtr->date = (result[4] & 0x0F) + ((result[4] & 0x30) >> 4) * 10;
	configPtr->month = (result[5] & 0x0F) + ((result[5] & 0x10) == BIT4) * 10;
	configPtr->year = (result[6] & 0x0F) + ((result[6] & 0xF0) >> 4) * 10
			+ 2000;
}


bool DS_GetTemp(float *temp) {
	if(DS_IsBusy()) {
		return false;
	}
	static uint8_t ctrl[2] = {DS_CONTROL};
	static uint8_t temp16[2];
	I2C_Read(DS3231_ADDR, DS_CONTROL, &ctrl[1], 1U);
	ctrl[1] |= 0x20;
	I2C_Write(DS3231_ADDR, ctrl, 2U);
	I2C_Read(DS3231_ADDR, DS_TEMP_MSB, (uint8_t*)&temp16, 2U);
	*temp = ((temp16[1] >> 6) | (temp16[0] << 2)) * 0.25;
	return true;
}
