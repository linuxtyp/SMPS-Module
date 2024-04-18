/*

*/

#ifndef SMPS_h
#define SMPS_h

#include "Arduino.h"

class SMPS
{
  public:
    SMPS();
    void CurrentLimitEnable(int value); //Status Reg, OCP
    void CurrentLimitDisable();
    void ClearCurrentFlag();
    String Info() //Ues ReadCDC, Status Reg Status Flag
    void OutputEnable(); //Mode Register
    void OutputDisable();
    void UseExternalVCC();
    void UseInternalVCC();
    void ShortCircuitEnable();
    void ShortCircuitDisable();
    void ClearShortFlag();//Status Reg, SCP Read

    
    
    char I2CAddress = 0x74//0x75
  private:
    char ReadCDC();

    I2C_t myI2C(I2C_NUM_0);
    int _pin;
};

#endif

