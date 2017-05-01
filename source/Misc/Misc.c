/*
 * Misc.c
 *
 *  Created on: 26 avr. 2017
 *      Author: hanch_000
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "Misc.h"


/*********             Internal macro             *********/

/* PORTC6 (number 78), U8[11]/SW2 */
#define BOARD_SW2_GPIO                                                     GPIOC   /*!< GPIO device name: GPIOC */
#define BOARD_SW2_PORT                                                     PORTC   /*!< PORT device name: PORTC */
#define BOARD_SW2_GPIO_PIN                                                    6U   /*!< PORTC pin index: 6 */
#define BOARD_SW2_PIN_NAME                                                  PTC6   /*!< Pin name */
#define BOARD_SW2_LABEL                                             "U8[11]/SW2"   /*!< Label */
#define BOARD_SW2_NAME                                                     "SW2"   /*!< Identifier name */
#define BOARD_SW2_DIRECTION                              kPIN_MUX_DirectionInput   /*!< Direction */

#define PCR_ODE_ENABLED               0x01u   /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
#define PCR_PE_ENABLED                0x01u   /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */

/*********             Internal types             *********/

/*********            Internal variables          *********/

/*********      Internal function declaration     *********/

/*********     Internal function implementation   *********/

/*********      Public function implementation    *********/
void Misc_EnableHv(bool en) {
	if (en) {
		PORTB->PCR[10] =
				((PORTB->PCR[10]
						& (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK
								| PORT_PCR_ISF_MASK))));
	} else {
		PORTB->PCR[10] = ((PORTB->PCR[10]
				& (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))
				| PORT_PCR_PS(PCR_PS_UP) | PORT_PCR_PE(PCR_PE_ENABLED));
	}
}

void PORTC_IRQHandler(void) {
	static bool hvEnabled = false;
	hvEnabled = !hvEnabled;
	Misc_EnableHv(hvEnabled);
	GPIO_ClearPinsInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
}

void Misc_InitButtonInt() {
	/*  Input pin configuration */
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
	NVIC_EnableIRQ(PORTC_IRQn);
	gpio_pin_config_t sw2_config =
	{
	    kGPIO_DigitalInput,
	    0,
	};
	/* Sets the input pin configuration */
	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw2_config);
}
