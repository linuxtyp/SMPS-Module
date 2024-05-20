/*

*/

#ifndef TPS_h
#define TPS_h

//#include "Arduino.h"

#include <Wire.h>
#include <iostream>
#include <string>
#include <cstdint>
#include "Registers.h"
//#include "TPS.h"
//#include  <Arduino.h>

class TPS
{
  public:
    TPS();
    void SetCurrentControl();
    void CurrentLimitEnable(); //Status Reg, OCP
    void CurrentLimitDisable();
    void ClearCurrentFlag();
    void SetCurrent(); //for current control
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



  private:
    char ReadCDC();
    bool ControlMode; //0 is voltage control, 1 is current control
    //Registers regs;
    float voltage;
    float current;
};









#endif
