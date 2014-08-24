#include "Arduino.h"

#ifndef I2COON_H
#define I2COON_H

void readRegister(volatile uint8_t* pReg, void* value);
void writeRegister(volatile uint8_t* pReg, void* value);
bool enableTWI(bool enable);
bool setI2CBitRate(int32_t bitRate);
uint8_t getTWIStatus();
void setTWISlaveAddress(uint8_t slaveAddress, bool acceptGeneralCall);
void initSlaveReceiverMode(uint8_t slaveAddress, bool acceptGeneralCall);
uint8_t getTWISlaveAddress();
bool isTWIInterruptSet();
void clearTWIInterrupt();
void clearTWIError();

char* debugTWIStateToString(uint8_t stateCode);


#define REG_TWBR  0xB8
#define REG_TWSR  0xB9
#define REG_TWAR  0xBA
#define REG_TWDR  0xBB
#define REG_TWCR  0xBC
#define REG_TWAMR 0xBD

enum TWISLRStatus_t {
  // Status codes for slave receiver mode
  RECV_SLAW_ACK = 0x60,                     // Own SLA+W has been received; ACK has been returned.
  ARB_LOST_SLAW_RECV_ACK = 0x68,            // Arbitration lost in SLA+R/W as Master; own SLAüW has been received; ACK has been returned.
  GEN_CALL_ADDR_RECV_ACK = 0x70,            // General call address has been received; ACK has been returned
  ARB_LOST_SLARW_GENCA_RECV_ACK = 0x78,     // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned.
  PREV_ADDR_OWN_SLAW_DATA_RECV_ACK = 0x80,  // Previously addressed with own SLA+W; data has been received; ACK has been returned.
  PREV_ADDR_OWN_SLAW_DATA_RECV_NACK = 0x88, // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned.
  PREV_ADDR_GEN_CALL_DATA_RECV_ACK = 0x90,  // Previously addressed with general call; data has been received; ACK has been returned.
  PREV_ADDR_GEN_CALL_DATA_RECV_NACK = 0x98, // Previously addressed with general call; data has been received; NOT ACK has been returned
  STOP_OR_RESTART_COND_RECV_W_ADS  = 0xA0, // A STOP condition or repeated START condition has been received while still addresses as Slave
};

enum TWIMiscState_t {
  NO_TWI_STATE_INFO_AVAILABLE = 0xF8, // No relevant state information available; TWINT = "0".
  BUS_ERROR_ILLEGAL_START_STOP_COND = 0x00, // Bus error due to an illegal START or STOP condition.
};

typedef struct {
  uint8_t 
  twbr;
} RegI2CoonTWBR_t;

typedef struct {
  uint8_t 
  twie  :1,
        :1,
  twen  :1,
  twwc  :1,
  twsto :1,
  twsta :1,
  twea  :1,
  twint :1;
} RegI2CoonTWCR_t;

typedef struct {
  uint8_t
  twps :2,
       :1,
  tws  :5;
} RegI2CoonTWSR_t;

typedef struct {
  uint8_t 
  twd;
} RegI2CoonTWDR_t;

typedef struct {
  uint8_t 
  twgce :1,
  twa   :7;
} RegI2CoonTWAR_t;

typedef struct {
  uint8_t
       : 1,
  twam : 7;
} RegI2CoonTWAMR_t;


// 328p registers
typedef struct {
  uint8_t
  pradc    :1,
  prusart0 :1,
  prspi    :1,
  prtim1   :1,
           :1,
  prtim0   :1,
  prtim2   :1,
  prtwi    :1;
} Reg328pPRR_t;

#endif /* I2COON_H */
