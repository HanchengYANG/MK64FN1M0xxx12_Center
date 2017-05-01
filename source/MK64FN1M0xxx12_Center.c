/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
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
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 
/**
 * @file    MK64FN1M0xxx12_Center.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "FreeRTOS.h"
#include "task.h"

/* TODO: insert other include files here. */
#include "I2C/DS3231/DS3231.h"
/* TODO: insert other definitions and declarations here. */
void UartListenTask(void *pvParameters);

void DsRtcCommTask(void *pvParameters);
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
	DS_Init();
    printf("Hardware initialization complete, start task init.\r\n");
    xTaskCreate(UartListenTask, "Uart listen", 1000, NULL, 33U, NULL);
    xTaskCreate(DsRtcCommTask, "Ds Rtc", 1000, NULL, 33U, NULL);

    vTaskStartScheduler();
    return 0 ;
}

void UartListenTask(void *pvParameters) {
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	printf("Uart listening...\r\n");
	while(1) {
		vTaskDelay(xDelay1000ms);
	}
}

void DsRtcCommTask(void *pvParameters) {
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	static uint8_t month[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	static uint8_t day[7][4] =
			{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	DS_DataStruct dsData;
	TickType_t previous = xTaskGetTickCount();
	float temperature = 0.0;
	while(1) {
		vTaskDelayUntil(&previous, xDelay1000ms);
		DS_GetDateTime(&dsData);
		DS_GetTemp(&temperature);
		printf("%02d:%02d:%02d, %s, %s %d, %d\ttemperature : %d C\r", dsData.hour, dsData.min,
				dsData.sec, day[dsData.day - 1], month[dsData.month - 1], dsData.date,
				dsData.year, (uint8_t)temperature);
	}
}
