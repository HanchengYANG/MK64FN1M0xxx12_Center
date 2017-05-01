/*
 * I2C_HAL.h
 *
 *  Created on: 2017年4月21日
 *      Author: hanch
 */

#ifndef I2C_HAL_I2C_HAL_H_
#define I2C_HAL_I2C_HAL_H_

#include "fsl_common.h"

/*********             Public macro             *********/
#define		I2C_RELEASE_SCL_PORT	PORTB
#define		I2C_RELEASE_SCL_PIN		2U
#define		I2C_RELEASE_SDA_PIN		3U
#define		I2C_RELEASE_SCL_GPIO	GPIOB
#define		I2C_RELEASE_SDA_GPIO	GPIOB
/*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
#define 	PCR_ODE_ENABLED         0x01u
/*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
#define 	PCR_PE_ENABLED          0x01u
/*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define 	PCR_PS_UP               0x01u

/*********             Public types             *********/

/*********            Public variables          *********/

/*********      Public function declaration     *********/

void I2C_Init();

void I2C_Write(uint8_t deviceAddr, uint8_t* txData, uint8_t len);

void I2C_Read(uint8_t deviceAddr, uint8_t regAddr, uint8_t* rxData, uint8_t len);

#endif /* I2C_HAL_I2C_HAL_H_ */
