#include "SMPS.h"


TPS tps();
SMPS::SMPS(){

}

void SMPS::OutputEnable(){
  tps.OutputEnable();
  //TPS::OutputEnable();
}
void SMPS::OutputDisable(){
  tps.OutputDisable();
  //TPS::OutputDisable();
}
