/*
 * Nixie.c
 *
 *  Created on: 2017年4月28日
 *      Author: hanch
 */

#include "Nixie.h"
#include "I2C/MCP23016/MCP23016.h"

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
