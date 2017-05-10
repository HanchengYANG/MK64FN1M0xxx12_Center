/*
 * NixieClockShell.h
 *
 *  Created on: 2017年5月7日
 *      Author: hanch
 */

#ifndef APP_NIXIECLOCKSHELL_H_
#define APP_NIXIECLOCKSHELL_H_

#include "fsl_shell.h"

/*********             Public macro             *********/

/*********             Public types             *********/

/*********            Public variables          *********/

/*********      Public function declaration     *********/

void NixieShell_ListnerTask(void *pvParameters);

void NixieShell_SendDataCallback(uint8_t *buf, uint32_t len);

void NixieShell_ReceiveDataCallback(uint8_t *buf, uint32_t len);

void NixieShell_Task(void *pvParameters);

#endif /* APP_NIXIECLOCKSHELL_H_ */
