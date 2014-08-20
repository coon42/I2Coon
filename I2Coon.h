#include "Arduino.h"

#ifndef I2COON_H
#define I2COON_H

bool setI2CBitRate(int32_t bitRate);


#define REG_TWBR  0xB8
#define REG_TWSR  0xB9
#define REG_TWAR  0xBA
#define REG_TWDR  0xBB
#define REG_TWCR  0xBC
#define REG_TWAMR 0xBD

typedef struct {
  uint8_t twbr;
} RegI2CoonTWBR;

typedef struct {
  uint8_t twie  : 1;
  uint8_t       : 1;
  uint8_t twen  : 1;
  uint8_t twwc  : 1;
  uint8_t twsto : 1;
  uint8_t twsta : 1;
  uint8_t twea  : 1;
  uint8_t twint : 1;
} RegI2CoonTWCR;

typedef struct {
  uint8_t twps : 2;
  uint8_t      : 1;
  uint8_t tws  : 5;
} RegI2CoonTWSR;

typedef struct {
  uint8_t twd;
} RegI2CoonTWDR;

typedef struct {
  uint8_t twgce : 1;
  uint8_t twa   : 7;
} RegI2CoonTWAR;

typedef struct {
  uint8_t      : 1;
  uint8_t twam : 7;
} RegI2CoonTWAMR;

#endif /* I2COON_H */
