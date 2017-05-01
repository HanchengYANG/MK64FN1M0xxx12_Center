/*
 * MCP23016.c
 *
 *  Created on: 2017年4月28日
 *      Author: hanch
 */

#include "MCP23016.h"
#include "I2C/HAL/I2C_HAL.h"

/*********             Internal macro             *********/

#define MUX_BASE_ADDR          0x20

//Input port
#define MCP23016_INPUT0        0X00
#define MCP23016_INPUT1        0X01
//Output port
#define MCP23016_OUTPUT0       0X02
#define MCP23016_OUTPUT1       0X03
//Polarity inversion port
#define MCP23016_POL0          0X04
#define MCP23016_POL1          0X05
//Configuration port
#define MCP23016_IODIR0        0X06
#define MCP23016_IODIR1        0X07
//interrupt capture registers
#define MCP23016_INTCAP0       0X08
#define MCP23016_INTCAP1       0X09
//I/O expander control register
#define MCP23016_IOCON0        0X0A
#define MCP23016_IOCON1        0X0B

/*********             Internal types             *********/

/*********            Internal variables          *********/
static uint8_t ioDirConfigList[2][3] = {
    {
      MCP23016_IODIR0,
      (uint8_t)~MUX0_PORT0_IODIR,
      (uint8_t)~MUX0_PORT1_IODIR
    }, {
      MCP23016_IODIR0,
      (uint8_t)~MUX1_PORT0_IODIR,
      (uint8_t)~MUX1_PORT1_IODIR
    }
};


/*********      Internal function declaration     *********/

static inline void Mux_InitSingleMux(Mux_Type mux);

/*********     Internal function implementation   *********/

static inline void Mux_InitSingleMux(Mux_Type mux) {
  /* Mux I/O direction */
  I2C_Write(MUX_BASE_ADDR + mux, ioDirConfigList[mux], sizeof(ioDirConfigList[mux]));
}

/*********      Public function implementation    *********/

void Mux_Init() {
  I2C_Init();
  Mux_InitSingleMux(Mux0);
  Mux_InitSingleMux(Mux1);
  Mux_WritePort(Mux0, Mux_Port0, 0);
  Mux_WritePort(Mux0, Mux_Port1, 0);
  Mux_WritePort(Mux1, Mux_Port0, 0);
  Mux_WritePort(Mux1, Mux_Port1, 0);
}

uint8_t Mux_ReadPort(Mux_Type mux, MuxPort_Type port) {
  uint8_t result;
  I2C_Read(MUX_BASE_ADDR + mux, MCP23016_INPUT0 + port, &result, 1);
  return result;
}

bool Mux_ReadPin(Mux_Type mux, MuxPort_Type port, uint8_t pin) {
  return (Mux_ReadPort(mux, port) & pin);
}

void Mux_WritePort(Mux_Type mux, MuxPort_Type port, uint8_t value) {
  uint8_t regAddrValue[2] = {MCP23016_OUTPUT0 + port, value};
  I2C_Write(MUX_BASE_ADDR + mux, regAddrValue, sizeof(regAddrValue));
}

void Mux_SetPin(Mux_Type mux, MuxPort_Type port, uint8_t pin) {
  Mux_WritePort(mux, port, Mux_ReadPort(mux, port) | pin);
}

void Mux_ClrPin(Mux_Type mux, MuxPort_Type port, uint8_t pin) {
  Mux_WritePort(mux, port, Mux_ReadPort(mux, port) & (~pin));
}
