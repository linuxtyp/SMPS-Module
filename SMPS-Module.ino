#include "TPS55288.h"
//#include "SMPS.h"
//s#include <HardwareSerial.h>


//SMPS smps;
TPS55288 tps;
void setup() {
  // put your setup code here, to run once:
  //smps.OutputDisable();
  tps.OutputDisable();
}

void loop() {
  // put your main code here, to run repeatedly:
  //smps.OutputDisable();
  delay(200);
}
