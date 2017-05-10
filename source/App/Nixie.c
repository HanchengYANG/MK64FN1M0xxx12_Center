/*
 * Nixie.c
 *
 *  Created on: 2017年4月28日
 *      Author: hanch
 */

#include "FreeRTOS.h"
#include "task.h"
#include "I2C/MCP23016/MCP23016.h"
#include "I2C/DS3231/DS3231.h"
#include "fsl_debug_console.h"
#include "Nixie.h"
#include "Misc/Misc.h"

/*********             Internal macro             *********/

#define         NIXIE_0         0x07
#define         NIXIE_1         0x06
#define         NIXIE_2         0x04
#define         NIXIE_3         0x05
#define         NIXIE_4         0x02
#define         NIXIE_5         0x03
#define         NIXIE_6         0x01
#define         NIXIE_7         0x00
#define         NIXIE_8         0x09
#define         NIXIE_9         0x08

/*********             Internal types             *********/

typedef enum {
  NixiePair0 = 0, NixiePair1, NixiePair2,
} NixiePairNum;

/*********            Internal variables          *********/

static uint8_t Nixie_NumberToMux[10] = {
NIXIE_0, NIXIE_1, NIXIE_2, NIXIE_3, NIXIE_4,
NIXIE_5, NIXIE_6, NIXIE_7, NIXIE_8, NIXIE_9 };

static bool DsRtc_UartOutputEnable;

/*********      Internal function declaration     *********/

static void Nixie_SetNumber(NixiePairNum pairNum, uint8_t num);

/*********     Internal function implementation   *********/

static void Nixie_SetNumber(NixiePairNum pairNum, uint8_t num) {
  uint8_t gpValue = (Nixie_NumberToMux[num % 10] << 4) | Nixie_NumberToMux[num / 10];
  if (num < 100) {
    switch (pairNum) {
    case NixiePair0:
      Mux_WritePort(Mux0, Mux_Port0, gpValue);
      break;
    case NixiePair1:
      Mux_WritePort(Mux0, Mux_Port1, gpValue);
      break;
    case NixiePair2:
      Mux_WritePort(Mux1, Mux_Port0, gpValue);
      break;
    }
  }
}

/*********      Public function implementation    *********/

void Nixie_Init() {
  Mux_Init();
}

void Nixie_SetTime(uint8_t h, uint8_t m, uint8_t s) {
  Nixie_SetNumber(NixiePair0, h);
  Nixie_SetNumber(NixiePair1, m);
  Nixie_SetNumber(NixiePair2, s);
}

void DsRtc_SetUartOutputEnable(bool en) {
	if(en) {
		PRINTF("printf time date to UART\r\n");
	}
	DsRtc_UartOutputEnable = en;
}

void DsRtc_Task(void *pvParameters) {
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	static uint8_t month[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	static uint8_t day[7][4] =
			{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	DS_DataStruct dsData;
	TickType_t previous = xTaskGetTickCount();
	DsRtc_UartOutputEnable = true;
	float temperature = 0.0;
	Misc_InitButtonInt();
	Nixie_Init();
	vTaskDelay(xDelay1000ms);
	PRINTF("\r\n");
	while(1) {
		vTaskDelayUntil(&previous, xDelay1000ms);
		DS_GetDateTime(&dsData);
		DS_GetTemp(&temperature);
		Nixie_SetTime(dsData.hour, dsData.min, dsData.sec);
		if(DsRtc_UartOutputEnable) {
			PRINTF("%02d:%02d:%02d, %s, %s %d, %d\ttemperature : %d C\r", dsData.hour, dsData.min,
					dsData.sec, day[dsData.day - 1], month[dsData.month - 1], dsData.date,
					dsData.year, (uint8_t)temperature);
		}
	}
}
