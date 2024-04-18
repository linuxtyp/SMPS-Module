/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Updated by Jason A. Cox, February 18, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SMPS.h"





SMPS::I2C_Hotplug(int SCL, int SDA)
{
  //_pin = pin;
}

void I2C_Hotplug::begin()
{
  //pinMode(_pin, OUTPUT);
}

void I2C_Hotplug::dot()
{
  //digitalWrite(_pin, HIGH);
  //delay(250);
  //digitalWrite(_pin, LOW);
  //delay(250);  
}

void I2C_Hotplug::dash()
{
  //digitalWrite(_pin, HIGH);
  //delay(1000);
  //digitalWrite(_pin, LOW);
  //delay(250);
}

