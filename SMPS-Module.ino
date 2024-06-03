#include <Wire.h>
#include "TPS55288.h"
#include "Registers.h"
#include <Adafruit_NeoPixel.h>
// Definiere die I2C-Pins für den ESP32
#define I2C_SCL 8
#define I2C_SDA 9
#define I2C_Baud 100000
#define LED_PIN 12
#define NUM_LEDS 1
#define ADC_PIN 1
//#define TPS55288_Addr 0x74
Adafruit_NeoPixel rgbled = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
float userVoltage = 0;

// Erstelle eine Instanz der TPS55288-Klasse
TPS55288 tps(I2C_SDA, I2C_SCL, I2C_Baud, Serial);
Registers tpsregs(8);
void setup() {
  Serial.begin(115200);
  tpsregs.setRegisterName(0,"REF_LSB");
  tpsregs.setBit(0,0,false,"VREF0");
  tpsregs.setBit(0,1,true,"VREF1");
  tpsregs.setBit(0,2,false,"VREF2");
  tpsregs.setBit(0,3,false,"VREF3");
  tpsregs.setBit(0,4,true,"VREF4");
  tpsregs.setBit(0,5,false,"VREF5");
  tpsregs.setBit(0,6,true,"VREF6");
  tpsregs.setBit(0,7,true,"VREF7");
  tpsregs.setRegisterName(1,"REF_MSB");
  tpsregs.setBit(1,0,false,"VREF8");
  tpsregs.setBit(1,1,false,"VREF9");
  tpsregs.setBit(1,2,false,"Reserved");
  tpsregs.setBit(1,3,false,"Reserved");
  tpsregs.setBit(1,4,false,"Reserved");
  tpsregs.setBit(1,5,false,"Reserved");
  tpsregs.setBit(1,6,false,"Reserved");
  tpsregs.setBit(1,7,false,"Reserved");
  tpsregs.setRegisterName(2,"IOUT_LIMIT");
  tpsregs.setBit(2,0,false,"CurrentLimitSetting0");
  tpsregs.setBit(2,1,false,"CurrentLimitSetting1");
  tpsregs.setBit(2,2,false,"CurrentLimitSetting2");
  tpsregs.setBit(2,3,false,"CurrentLimitSetting3");
  tpsregs.setBit(2,4,false,"CurrentLimitSetting4");
  tpsregs.setBit(2,5,false,"CurrentLimitSetting5");
  tpsregs.setBit(2,6,false,"CurrentLimitSetting6");
  tpsregs.setBit(2,7,false,"CurrentLimitEN");
  tpsregs.setRegisterName(3,"VOUT_SR");
  tpsregs.setBit(3,0,true,"SlewRate0");
  tpsregs.setBit(3,1,false,"SlewRate1");
  tpsregs.setBit(3,2,false,"Reserved");
  tpsregs.setBit(3,3,false,"Reserved");
  tpsregs.setBit(3,4,false,"OCP_DELAY0");
  tpsregs.setBit(3,5,false,"OCP_DELAY1");
  tpsregs.setBit(3,6,false,"Reserved");
  tpsregs.setBit(3,7,false,"Reserved");
  tpsregs.setRegisterName(4,"VOUT_FS");
  tpsregs.setBit(4,0,true,"INTFB0");
  tpsregs.setBit(4,1,true,"INTFB1");
  tpsregs.setBit(4,2,false,"Reserved");
  tpsregs.setBit(4,3,false,"Reserved");
  tpsregs.setBit(4,4,false,"Reserved");
  tpsregs.setBit(4,5,false,"Reserved");
  tpsregs.setBit(4,6,false,"Reserved");
  tpsregs.setBit(4,7,false,"FeedBack");
  tpsregs.setRegisterName(5,"CDC");
  tpsregs.setBit(5,0,false,"CompensationForVoltageDroop0");
  tpsregs.setBit(5,1,false,"CompensationForVoltageDroop1");
  tpsregs.setBit(5,2,false,"CompensationForVoltageDroop2");
  tpsregs.setBit(5,3,false,"CDCOption");
  tpsregs.setBit(5,4,false,"Reserved");
  tpsregs.setBit(5,5,true, "OVP_MASK");
  tpsregs.setBit(5,6,true, "OCP_MASK");
  tpsregs.setBit(5,7,true, "SC_MASK");
  tpsregs.setRegisterName(6,"MODE");
  tpsregs.setBit(6,0,false,"MODE");
  tpsregs.setBit(6,1,false,"PFM");
  tpsregs.setBit(6,2,false,"I2CADD");
  tpsregs.setBit(6,3,false,"VCC");
  tpsregs.setBit(6,4,false,"DISCHG");
  tpsregs.setBit(6,5,true,"HICCUP");
  tpsregs.setBit(6,6,false,"FSWDBL");
  tpsregs.setBit(6,7,false,"OE");
  tpsregs.setRegisterName(7,"STATUS");
  tpsregs.setBit(7,0,true,"STATUS0");
  tpsregs.setBit(7,1,true,"STATUS1");
  tpsregs.setBit(7,2,false,"Reserved");
  tpsregs.setBit(7,3,false,"Reserved");
  tpsregs.setBit(7,4,false,"Reserved");
  tpsregs.setBit(7,5,false,"OVP");
  tpsregs.setBit(7,6,false,"OCP");
  tpsregs.setBit(7,7,false,"SCP");
  // Initialisiere die serielle Kommunikation zur Ausgabe
  rgbled.begin();
  rgbled.show();

  
  // Initialisiere die I2C-Kommunikation
  //Wire1.begin(I2C_SDA, I2C_SCL);
  
  // Initialisiere das TPS55288-Modul
  //tps = TPS55288(I2C_SDA, I2C_SCL);
  
  // Setze den Spannungsregelmodus
  tps.SetVoltageControl();
  Serial.println("Set Voltagecontrol");
  
  // Aktiviere den Ausgang
  //tps.OutputEnable();
  delay(2000);
  tps.OutputDisable();
  Serial.println("Output Disabled");
  delay(2000);
}

void loop() {
  // Variable to store the voltage input by the user
  
  //rgbled.setPixelColor(1, (255,255,255));
  //rgbled.show();
  tps.SetCurrentLimit(2.0);
  //Serial.println("Current Limit Set.");
  tps.CurrentLimitEnable();
  //Serial.println("Current Limit Enabled");
  // Prompt the user to input the voltage
  Serial.println(readCurrent());
  delay(1000);
  Serial.println("Enter the desired voltage (in volts): ");
  start:
  while (!Serial.available()) {
  }
  // Read the voltage input from the user
  userVoltage = Serial.parseFloat();
  //userVoltage = 5;
  if (userVoltage == 0)
  {
    goto start;
  } else if (userVoltage>20){
    for (int i = 0 ; i < 8 ; i++)
    {
      //Serial.println(tps.ReadReg(i));
      tpsregs.setRegister(i,tps.ReadReg(i));
    }
    Serial.println(tpsregs.StatusRegs().c_str());
  }
  
  // Set the voltage
  tps.SetVoltage(userVoltage);
  Serial.print("Set Voltage: ");
  Serial.println(userVoltage);
  
  tps.OutputEnable();
  Serial.println("Output Enabled");
  rgbled.setPixelColor(1,(255,0,0));
  rgbled.show();
  delay(1000);
}





float readCurrent() {
  // Read the raw ADC value (12-bit resolution on ESP32, values range from 0 to 4095)
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  float adcValue = analogRead(ADC_PIN);
  //Serial.print("ADC: ");
  //Serial.println(adcValue);
  // Convert the ADC value to a voltage
  // ESP32 has a 3.3V reference voltage
  //float voltage = ((2.5/4096)*adcValue)/50.0;
  float voltage = (adcValue * 1.947 / 4096)/50;
  //Serial.print("Voltage: ");
  //Serial.println(voltage);
  // Calculate the current
  // The voltage is amplified by 50, so we need to divide by 50
  // The shunt resistor is 10 mOhm (0.01 Ohm)
  float current = voltage / (0.01);

  return current;  // Return the current in Amperes
}