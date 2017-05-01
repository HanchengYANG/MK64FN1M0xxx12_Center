/*
 * Nixie.h
 *
 *  Created on: 2017年4月28日
 *      Author: hanch
 */

#ifndef APP_NIXIE_H_
#define APP_NIXIE_H_

#include "fsl_common.h"

/*********             Public macro             *********/

/*********             Public types             *********/

/*********            Public variables          *********/

/*********      Public function declaration     *********/

void Nixie_Init();

void Nixie_SetTime(uint8_t h, uint8_t m, uint8_t s);

#endif /* APP_NIXIE_H_ */
