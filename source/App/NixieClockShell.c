/*
 * NixieClockShell.c
 *
 *  Created on: 2017年5月7日
 *      Author: hanch
 */

#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "App/Nixie.h"
#include "NixieClockShell.h"

/*********             Internal macro             *********/

/*********             Internal types             *********/

/*********            Internal variables          *********/

static shell_context_struct NixieShell_Context;

static QueueHandle_t NixieShell_QueueHandle;

static bool NixieShell_CmdEnable;

/*********      Internal function declaration     *********/

static void NixieShell_SetEnable(bool en);

static void NixieShell_CalibDate();

static void NixieShell_CalibTime();

static int32_t NixieShell_CalibrateDS(p_shell_context_t context, int32_t argc, char **argv);

static int32_t NixieShell_EnableCmd(p_shell_context_t context, int32_t argc, char **argv);

/*********     Internal function implementation   *********/

static void NixieShell_CalibDate() {

}

static void NixieShell_CalibTime() {

}

static void NixieShell_SetEnable(bool en) {
	NixieShell_CmdEnable = en;
}

static int32_t NixieShell_EnableCmd(p_shell_context_t context, int32_t argc, char **argv) {
	static bool cmdEnable = false;
	if(cmdEnable) {
		cmdEnable = false;
		PRINTF("\r\nLeave cmd\r\n");
	} else {
		cmdEnable = true;
		PRINTF("\r\nEnter cmd\r\n");
	}
	DsRtc_SetUartOutputEnable(!cmdEnable);
	NixieShell_SetEnable(cmdEnable);
	return 0;
}

static int32_t NixieShell_CalibrateDS(p_shell_context_t context, int32_t argc, char **argv) {
	char *calibType = argv[1];
	if(strcmp(calibType, "date") == 0) {
		xQueueSendToBack(NixieShell_QueueHandle, NixieShell_CalibDate, 0);
	}
	if (strcmp(calibType, "time") == 0) {
		xQueueSendToBack(NixieShell_QueueHandle, NixieShell_CalibTime, 0);
	}
	return 0;
}

/*********      Public function implementation    *********/
void NixieShell_ListnerTask(void *pvParameters) {
	SHELL_Init(&NixieShell_Context, NixieShell_SendDataCallback,
			NixieShell_ReceiveDataCallback, PRINTF, "NixieClocl>> ");
	static const shell_command_context_t xActivateCmd =
			{ "$$$",
					"\r\n$$$ for enter command mode\r\n",
					NixieShell_EnableCmd, 0 };
	SHELL_RegisterCommand(&xActivateCmd);
	static const shell_command_context_t xCalibCmd =
			{ "dscalib",
					"\r\n \"dscalib arg1 arg2\":\r\n Usage:\r\n\targ1: date|time\r\n\targ2:\r\n\t\tdate->yyyymmdd\r\n\t\ttime->hhmmss\r\n",
					NixieShell_CalibrateDS, 2 };
	SHELL_RegisterCommand(&xCalibCmd);
	SHELL_Main(&NixieShell_Context);
	NixieShell_CmdEnable = false;
}


void NixieShell_SendDataCallback(uint8_t *buf, uint32_t len) {
	if(NixieShell_CmdEnable) {
		while(len--) {
			PUTCHAR(*(buf++));
		}
	}
}

void NixieShell_ReceiveDataCallback(uint8_t *buf, uint32_t len) {
	static uint8_t ch;
	while (len--) {
		ch = GETCHAR();
		if (NixieShell_CmdEnable || ch == '$' || ch == '\r') {
			*(buf++) = ch;
		}
	}
}

void NixieShell_Task(void *pvParameters) {
	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );
	NixieShell_QueueHandle = xQueueCreate(10, sizeof(uint32_t));
	void (*CmdCallback)() = NULL;
	while(1) {
		//Wait for shell command
		if(xQueueReceive(NixieShell_QueueHandle, &CmdCallback, xDelay1000ms)) {
			if(CmdCallback != NULL) {
				CmdCallback();
				CmdCallback = NULL;
			}
		}
	}
}
