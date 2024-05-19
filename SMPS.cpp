/*
Start Bit: 0
7 Bit Address
Direction Bit: 0 -> Write, 1 -> Read
-- Ack --
Register Address
-- Ack --
Data Address
-- Ack --
-- Ack --
Stop Bit: 1
*/

//#include "Arduino.h"
#include "SMPS.h"

#define I2C_SCL 13
#define I2C_SDA 14
#define TPS_Addr 0x74 //Default if I2CADDR Flag ture-> 0x75




Registers regs(8);
SMPS::SMPS(){
  Wire1.begin(I2C_SDA, I2C_SCL);
  //Serial.begin(115200);
  regs.setRegisterName(0,"REF_LSB");
  regs.setBit(0,0,false,"VREF");
  regs.setBit(0,1,true,"VREF");
  regs.setBit(0,2,false,"VREF");
  regs.setBit(0,3,false,"VREF");
  regs.setBit(0,4,true,"VREF");
  regs.setBit(0,5,false,"VREF");
  regs.setBit(0,6,true,"VREF");
  regs.setBit(0,7,true,"VREF");

  regs.setRegisterName(1,"REF_MSB");
  regs.setBit(1,0,false,"VREF");
  regs.setBit(1,1,false,"VREF");
  regs.setBit(1,2,false,"Reserved");
  regs.setBit(1,3,false,"Reserved");
  regs.setBit(1,4,false,"Reserved");
  regs.setBit(1,5,false,"Reserved");
  regs.setBit(1,6,false,"Reserved");
  regs.setBit(1,7,false,"Reserved");


  regs.setRegisterName(2,"IOUT_LIMIT");
  regs.setBit(2,0,false,"CurrentLimitSetting");
  regs.setBit(2,1,false,"CurrentLimitSetting");
  regs.setBit(2,2,false,"CurrentLimitSetting");
  regs.setBit(2,3,false,"CurrentLimitSetting");
  regs.setBit(2,4,false,"CurrentLimitSetting");
  regs.setBit(2,5,false,"CurrentLimitSetting");
  regs.setBit(2,6,false,"CurrentLimitSetting");
  regs.setBit(2,7,false,"CurrentLimitEN");

  regs.setRegisterName(3,"VOUT_SR");
  regs.setBit(3,0,true,"SlewRate");
  regs.setBit(3,1,false,"SlewRate");
  regs.setBit(3,2,false,"Reserved");
  regs.setBit(3,3,false,"Reserved");
  regs.setBit(3,4,false,"OCP_DELAY");
  regs.setBit(3,5,false,"OCP_DELAY");
  regs.setBit(3,6,false,"Reserved");
  regs.setBit(3,7,false,"Reserved");

  regs.setRegisterName(4,"VOUT_FS");
  regs.setBit(4,0,true,"INTFB");
  regs.setBit(4,1,true,"INTFB");
  regs.setBit(4,2,false,"Reserved");
  regs.setBit(4,3,false,"Reserved");
  regs.setBit(4,4,false,"Reserved");
  regs.setBit(4,5,false,"Reserved");
  regs.setBit(4,6,false,"Reserved");
  regs.setBit(4,7,false,"FeedBack");

  regs.setRegisterName(5,"CDC");
  regs.setBit(5,0,false,"CompensationForVoltageDroop");
  regs.setBit(5,1,false,"CompensationForVoltageDroop");
  regs.setBit(5,2,false,"CompensationForVoltageDroop");
  regs.setBit(5,3,false,"CDCOption");
  regs.setBit(5,4,false,"Reserved");
  regs.setBit(5,5,true, "OVP_MASK");
  regs.setBit(5,6,true, "OCP_MASK");
  regs.setBit(5,7,true, "SC_MASK");

  regs.setRegisterName(6,"MODE");
  regs.setBit(6,0,false,"MODE");
  regs.setBit(6,1,false,"PFM");
  regs.setBit(6,2,false,"I2CADD");
  regs.setBit(6,3,false,"VCC");
  regs.setBit(6,4,false,"DISCHG");
  regs.setBit(6,5,true,"HICCUP");
  regs.setBit(6,6,false,"FSWDBL");
  regs.setBit(6,7,false,"OE");

  regs.setRegisterName(7,"STATUS");
  regs.setBit(7,0,true,"STATUS");
  regs.setBit(7,1,true,"STATUS");
  regs.setBit(7,2,false,"Reserved");
  regs.setBit(7,3,false,"Reserved");
  regs.setBit(7,4,false,"Reserved");
  regs.setBit(7,5,false,"OVP");
  regs.setBit(7,6,false,"OCP");
  regs.setBit(7,7,false,"SCP");
  OutputDisable();

}
void SMPS::OutputEnable(){
  Wire1.beginTransmission(TPS_Addr);
  regs.setBit("OE",true);
  Wire1.write(regs.RegisterAddress("MODE"));
  Wire1.write(regs.RegisterValue("MODE"));
  Wire1.endTransmission();
  //Serial.println(regs.RegisterAddress("MODE"));
  //Serial.println(regs.RegisterValue("MODE"));
}
void SMPS::OutputDisable(){
  Wire1.beginTransmission(TPS_Addr);
  regs.setBit("OE",false);
  Wire1.write(regs.RegisterAddress("MODE"));
  Wire1.write(regs.RegisterValue("MODE"));
  Wire1.endTransmission();
  //Serial.println(regs.RegisterAddress("MODE"));
  //Serial.println(regs.RegisterValue("MODE"));
}

void SMPS::Info(){
  regs.printRegisters();
}



void SMPS::SetVoltage(float voltage)
{
  if (!SMPS::ControlMode)
  {
    SMPS::voltage = voltage;
    /*Wire1.beginTransmission(TPS_Addr);
    regs.(setBit("OE",false));
    Wire1.write(regs.RegisterAddress("MODE"));
    Wire1.write(regs.RegisterValue("MODE"));
    Wire1.endTransmission();*/
  }
}

void SMPS::SetVoltageControl()
{
  SMPS::ControlMode = false;
}

void SMPS::SetCurrentControl()
{
  SMPS::ControlMode = true;
}
