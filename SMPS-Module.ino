#include "SMPS.h"
//s#include <HardwareSerial.h>


SMPS smps;
void setup() {
  // put your setup code here, to run once:
  smps.OutputDisable();
}

void loop() {
  // put your main code here, to run repeatedly:
  smps.OutputDisable();
  delay(200);
}
