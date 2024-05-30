/*

*/

#ifndef TPS55288_h
#define TPS55288_h

//#include "Arduino.h"

#include <Wire.h>
#include <iostream>
#include <string>
#include <cstdint>
#include "Registers.h"
//#include "debug.h"
//#include "TPS55288.h"
//#include  <Arduino.h>

class TPS55288
{
  protected:
    int I2C_SDA;
    int I2C_SCL;
    int I2C_Baud;
    bool ControlMode; //0 is voltage control, 1 is current control
    float voltage;
    float current;
    bool logging;

  public:
    TPS55288(int I2C_SDA, int I2C_SCL, int I2C_Baud);
    void SetCurrentControl();
    void CurrentLimitEnable(); //Status Reg, OCP
    void CurrentLimitDisable();
    void ClearCurrentFlag();
    void CurrentLimit(bool state); //for current control
    void SetCurrentLimit(float current); //for voltage control

    void Info(); //Ues ReadCDC, Status Reg Status Flag

    void OutputEnable(); //Mode Register
    void OutputDisable();

    void UseExternalVCC();
    void UseInternalVCC();

    void ShortCircuitProtectionEnable();
    void ShortCircuitProtectionDisable();
    void ClearShortFlag();//Status Reg, SCP Read
    void SetVoltage(float voltage); //for voltage control
    void SetVoltageLimit(float voltage); //for current control
    void SetVoltageControl();
    void setLog(bool state);
    void setOutput(bool state);

  private:
    char ReadCDC();
    void WriteI2CRegister(std::string regName, uint8_t count);
    void WriteI2CRegister(std::string regName);
    void log(std::string logString);
};









#endif
