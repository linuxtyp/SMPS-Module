#include "SMPS.h"


TPS55288 TPS55288();
SMPS::SMPS(){

}

void SMPS::OutputEnable(){
  TPS55288.OutputEnable();
  //TPS55288::OutputEnable();
}
void SMPS::OutputDisable(){
  TPS55288.OutputDisable();
  //TPS55288::OutputDisable();
}
