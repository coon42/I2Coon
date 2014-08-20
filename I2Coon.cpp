#include "I2Coon.h"


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
