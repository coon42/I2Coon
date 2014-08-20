#include "I2Coon.h"

void setup() {
  Serial.begin(9600);
  Serial.println("I2Coon dev Sample.");
  
  bool success = setI2CBitRate(612);
  

  
  Serial.print("Success: "); Serial.println(success);
}

void loop() {
  
}
