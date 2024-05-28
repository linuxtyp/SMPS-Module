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
#include "TPS55288.h"

#define TPS55288_Addr 0x74 //Default if I2CADDR Flag ture-> 0x75
#define SHUNT 0.01 //Ohm



Registers regs(8);
TPS55288::TPS55288(int I2C_SDA, int I2C_SCL, int I2C_Baud){
  TPS55288::I2C_SDA = I2C_SDA;
  TPS55288::I2C_SCL = I2C_SCL;
  TPS55288::I2C_Baud = I2C_Baud;
  setLog(true);
  log("i2c online");
  //Serial.begin(115200);
  regs.setRegisterName(0,"REF_LSB");
  regs.setBit(0,0,false,"VREF0");
  regs.setBit(0,1,true,"VREF1");
  regs.setBit(0,2,false,"VREF2");
  regs.setBit(0,3,false,"VREF3");
  regs.setBit(0,4,true,"VREF4");
  regs.setBit(0,5,false,"VREF5");
  regs.setBit(0,6,true,"VREF6");
  regs.setBit(0,7,true,"VREF7");

  regs.setRegisterName(1,"REF_MSB");
  regs.setBit(1,0,false,"VREF0");
  regs.setBit(1,1,false,"VREF1");
  regs.setBit(1,2,false,"Reserved");
  regs.setBit(1,3,false,"Reserved");
  regs.setBit(1,4,false,"Reserved");
  regs.setBit(1,5,false,"Reserved");
  regs.setBit(1,6,false,"Reserved");
  regs.setBit(1,7,false,"Reserved");


  regs.setRegisterName(2,"IOUT_LIMIT");
  regs.setBit(2,0,false,"CurrentLimitSetting0");
  regs.setBit(2,1,false,"CurrentLimitSetting1");
  regs.setBit(2,2,false,"CurrentLimitSetting2");
  regs.setBit(2,3,false,"CurrentLimitSetting3");
  regs.setBit(2,4,false,"CurrentLimitSetting4");
  regs.setBit(2,5,false,"CurrentLimitSetting5");
  regs.setBit(2,6,false,"CurrentLimitSetting6");
  regs.setBit(2,7,false,"CurrentLimitEN");

  regs.setRegisterName(3,"VOUT_SR");
  regs.setBit(3,0,true,"SlewRate0");
  regs.setBit(3,1,false,"SlewRate1");
  regs.setBit(3,2,false,"Reserved");
  regs.setBit(3,3,false,"Reserved");
  regs.setBit(3,4,false,"OCP_DELAY0");
  regs.setBit(3,5,false,"OCP_DELAY1");
  regs.setBit(3,6,false,"Reserved");
  regs.setBit(3,7,false,"Reserved");

  regs.setRegisterName(4,"VOUT_FS");
  regs.setBit(4,0,true,"INTFB0");
  regs.setBit(4,1,true,"INTFB1");
  regs.setBit(4,2,false,"Reserved");
  regs.setBit(4,3,false,"Reserved");
  regs.setBit(4,4,false,"Reserved");
  regs.setBit(4,5,false,"Reserved");
  regs.setBit(4,6,false,"Reserved");
  regs.setBit(4,7,false,"FeedBack");

  regs.setRegisterName(5,"CDC");
  regs.setBit(5,0,false,"CompensationForVoltageDroop0");
  regs.setBit(5,1,false,"CompensationForVoltageDroop1");
  regs.setBit(5,2,false,"CompensationForVoltageDroop2");
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
  regs.setBit(7,0,true,"STATUS0");
  regs.setBit(7,1,true,"STATUS1");
  regs.setBit(7,2,false,"Reserved");
  regs.setBit(7,3,false,"Reserved");
  regs.setBit(7,4,false,"Reserved");
  regs.setBit(7,5,false,"OVP");
  regs.setBit(7,6,false,"OCP");
  regs.setBit(7,7,false,"SCP");
  Wire1.begin(I2C_SDA, I2C_SCL, I2C_Baud);
  //delay(500);
  //OutputDisable(); //Bootloop
  log("Initialization successfull");
}
void TPS55288::OutputEnable(){
  setOutput(true);
}
void TPS55288::OutputDisable(){
  setOutput(false);
}

void TPS55288::Info(){
  regs.printRegisters();
}

void TPS55288::SetVoltage(float voltage)
{
  if (!TPS55288::ControlMode)
  {
    //saving the voltage in the library
    TPS55288::voltage = voltage;
    // fb ratios from the datasheet
    const float fbRatios[] = {0.2256, 0.1128, 0.0752, 0.0564}; 
    // Maximum reference voltage in V
    const float maxRefVoltage = 1.2;  

    float refVoltage;
    uint16_t refValue;
    uint8_t fbIndex = 0;

    // Select the appropriate feedback ratio
    for (int i = 0; i < 4; i++) 
    {
      refVoltage = voltage / fbRatios[i];
      if (refVoltage <= maxRefVoltage) {
          fbIndex = i;
          break;
      }
    }
    // Converting float to uint16_t
    refValue = static_cast<uint16_t>(refVoltage / fbRatios[fbIndex]);

    // starting the i2c transmission
    Wire1.beginTransmission(TPS55288_Addr);
    // sending register address and value for the lsb
    WriteI2CRegister("REF_LSB", refValue);
    // sending register address and value for the msb
    WriteI2CRegister("REF_MSB", refValue>>8);

    // send register address and value for the feedback ratio
    regs.setRegister("VOUT_FS", (regs.RegisterValue("VOUT_FS")&0xFC) | (fbIndex & 0x03 ));
    Wire1.write(regs.RegisterAddress("VOUT_FS"));
    Wire1.write(regs.RegisterValue("VOUT_FS"));

    // ending the i2c transmission
    Wire1.endTransmission();
  }
}
void TPS55288::SetCurrentLimit(float current){
  //0A
  //0.5mV/10mOhm=50mA
  //1mV/10mOhm100mA
  //150mA
  //200mA
  float voltage = current * SHUNT;
  // Calculate the register value
  uint8_t regValue = (uint8_t)(voltage / 0.0005); // 1 bit = 0.5 mV
  // Ensure the register value does not exceed the maximum allowed value (127)
  if (regValue > 127) {
    regValue = 127;
  }
  
  WriteI2CRegister("IOUT_LIMIT",(regs.State("CurrentLimitEN") << 7) | regValue);
  
}
void TPS55288::SetVoltageControl()
{
  // setting the control mode to voltage control
  // 0 = voltage control, 1= current control
  TPS55288::ControlMode = false;
}

void TPS55288::SetCurrentControl()
{
  // setting the control mode to current control
  // 0 = voltage control, 1= current control
  TPS55288::ControlMode = true;
}


void TPS55288::WriteI2CRegister(std::string regName, uint8_t value)
{
  // a routine for rewriting a whole register with a integer
  regs.setRegister(regName, (value & 0xFF));
  Wire1.write(regs.RegisterAddress(regName));
  Wire1.write(regs.RegisterValue(regName));
}

void TPS55288::setLog(bool state)
{
  logging = state;
}

void TPS55288::log(std::string logString)
{
  if (logging)
  {
    std::cerr << logString << std::endl;
  }
}
void TPS55288::CurrentLimitEnable(){
  CurrentLimit(true);
}
void TPS55288::CurrentLimitDisable(){
  CurrentLimit(false);
}
void TPS55288::CurrentLimit(bool state){
  Wire1.beginTransmission(TPS55288_Addr);
  log("starting transmission");
  regs.setBit("CurrentLimitEN",state);
  Wire1.write(regs.RegisterAddress("IOUT_LIMIT"));
  log("register address sent");
  Wire1.write(regs.RegisterValue("IOUT_LIMIT"));
  log("register value sent");
  uint8_t error = Wire1.endTransmission();
  log(std::to_string(error));
  std::cerr << "ending transmission" << std::endl;
}
void TPS55288::setOutput(bool state)
{
  Wire1.beginTransmission(TPS55288_Addr);
  log("starting transmission");
  regs.setBit("OE",state);
  Wire1.write(regs.RegisterAddress("MODE"));
  log("register address sent");
  Wire1.write(regs.RegisterValue("MODE"));
  log("register value sent");
  uint8_t error = Wire1.endTransmission();
  log(std::to_string(error));
  std::cerr << "ending transmission" << std::endl;
  //Serial.println(regs.RegisterAddress("MODE"));
  //Serial.println(regs.RegisterValue("MODE"));
}