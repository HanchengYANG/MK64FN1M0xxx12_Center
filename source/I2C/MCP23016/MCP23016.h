/*
 * MCP23016.h
 *
 *  Created on: 2017年4月28日
 *      Author: hanch
 */

#ifndef I2C_MCP23016_MCP23016_H_
#define I2C_MCP23016_MCP23016_H_

#include "fsl_common.h"

/*********             Public macro             *********/

/* IO direction configuration */
/* Mux0 */
#define         MUX0_PORT0_IODIR        0xFF
#define         MUX0_PORT1_IODIR        0xFF
/* Mux1 */
#define         MUX1_PORT0_IODIR        0xFF
#define         MUX1_PORT1_IODIR        0xFF

/*********             Public types             *********/

typedef enum{
    Mux_Port0 = 0, Mux_Port1 = 1
} MuxPort_Type;

typedef enum {
  Mux0 = 0, Mux1 = 1//, Mux2 = 2
} Mux_Type;

/*********            Public variables          *********/

/*********      Public function declaration     *********/

void Mux_Init();

uint8_t Mux_ReadPort(Mux_Type mux, MuxPort_Type port);

bool Mux_ReadPin(Mux_Type mux, MuxPort_Type port, uint8_t pin);

void Mux_WritePort(Mux_Type mux, MuxPort_Type port, uint8_t value);

void Mux_SetPin(Mux_Type mux, MuxPort_Type port, uint8_t pin);

void Mux_ClrPin(Mux_Type mux, MuxPort_Type port, uint8_t pin);

#endif /* I2C_MCP23016_MCP23016_H_ */
