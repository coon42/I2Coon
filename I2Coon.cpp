#include "I2Coon.h"

void readRegister(volatile uint8_t* pAtmegaReg, void* value) {
  *(uint8_t*)value = *pAtmegaReg;
}

void writeRegister(volatile uint8_t* pAtmegaReg, void* value) {
  *pAtmegaReg = *(uint8_t*)value;
}

bool enableTWI(bool enable) {
  Reg328pPRR_t prr;
  readRegister(&PRR, &prr);
  prr.prtwi = enable ? 0 : 1;
  writeRegister(&PRR, &prr);
}

bool isTWIInterruptSet() {
  RegI2CoonTWCR_t twcr;
  readRegister(&TWCR, &twcr);
  return twcr.twint == 1 ? true : false;
}

void clearTWIInterrupt() {
  RegI2CoonTWCR_t twcr;

  readRegister(&TWCR, &twcr);
  twcr.twint = 1;
  writeRegister(&TWCR, &twcr);  
}

void clearTWIError() {
  RegI2CoonTWCR_t twcr;

  readRegister(&TWCR, &twcr);
  twcr.twsto = 1;
  twcr.twint = 1;
  writeRegister(&TWCR, &twcr);
}

bool setI2CBitRate(int32_t bitRate) {
  Serial.println("setI2CBitRate()");
  uint8_t prescaler = 1;
  
  if(bitRate > 400000)
    return false;
  if(bitRate > 38020)
    prescaler = 1;
  else if(bitRate > 19310)
    prescaler = 2;
  else if(bitRate > 9728)
    prescaler = 4;
  else if(bitRate > 4883)
    prescaler = 8;
  else if(bitRate > 2446)
    prescaler = 16;
  else if(bitRate > 1224)
    prescaler = 32;
  else if(bitRate > 611)
    prescaler = 64;
  else
    return false;
    
  // See Chapter 22.5.2 (page 215)
  // TODO: optimize formular?
  
  TWSR = prescaler & 0x03;
  TWBR = (F_CPU / bitRate - 16) / (2 * prescaler);
  
  Serial.print("bitRate = "); Serial.println(bitRate);
  Serial.print("prescaler = "); Serial.println(prescaler);
  Serial.print("TWBR = "); Serial.println(TWBR);
  
  return true;
}

void setTWISlaveAddress(uint8_t slaveAddress, bool acceptGeneralCall) {
  RegI2CoonTWAR_t twar;
  readRegister(&TWAR, &twar);
  twar.twa = slaveAddress;
  twar.twgce = acceptGeneralCall ? 1 : 0;
  writeRegister(&TWAR, &twar);
}

void initSlaveReceiverMode(uint8_t slaveAddress, bool acceptGeneralCall) {
  setTWISlaveAddress(slaveAddress, acceptGeneralCall);
  
  // Enter slave mode
  RegI2CoonTWCR_t twcr;
  readRegister(&TWCR, &twcr);
  twcr.twen  = 1;
  twcr.twea  = 1;
  twcr.twsta = 0;
  twcr.twsto = 0;
  writeRegister(&TWCR, &twcr);
}

uint8_t getTWIStatus() {
  return TWSR & 0xF8;
}

uint8_t getTWISlaveAddress() {
  RegI2CoonTWAR_t twar;
  readRegister(&TWAR, &twar);
  
  return twar.twa;
}

char* debugTWIStateToString(uint8_t stateCode) {
  switch(stateCode) {
    
    // State codes for slave receiver mode
    case RECV_SLAW_ACK: return "RECV_SLAW_ACK";
    case ARB_LOST_SLAW_RECV_ACK: return "ARB_LOST_SLAW_RECV_ACK";
    case GEN_CALL_ADDR_RECV_ACK: return "GEN_CALL_ADDR_RECV_ACK";
    case ARB_LOST_SLARW_GENCA_RECV_ACK: return "ARB_LOST_SLARW_GENCA_RECV_ACK";
    case PREV_ADDR_OWN_SLAW_DATA_RECV_ACK: return "PREV_ADDR_OWN_SLAW_DATA_RECV_ACK";
    case PREV_ADDR_OWN_SLAW_DATA_RECV_NACK: return "PREV_ADDR_OWN_SLAW_DATA_RECV_NACK";
    case PREV_ADDR_GEN_CALL_DATA_RECV_ACK: return "PREV_ADDR_GEN_CALL_DATA_RECV_ACK";
    case PREV_ADDR_GEN_CALL_DATA_RECV_NACK: return "PREV_ADDR_GEN_CALL_DATA_RECV_NACK";
    case STOP_OR_RESTART_COND_RECV_W_ADS: return "STOP_OR_RESTART_COND_RECV_W_ADS";
    
    // misc states
    case NO_TWI_STATE_INFO_AVAILABLE: return "NO_TWI_STATE_INFO_AVAILABLE";
    case BUS_ERROR_ILLEGAL_START_STOP_COND: return "BUS_ERROR_ILLEGAL_START_STOP_COND";
    default: return "unknown TWI state.";
  }
}
