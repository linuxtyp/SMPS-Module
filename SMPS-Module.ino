#include <Wire.h>
#include "TPS55288.h"
//#include "debug.h"


// Definiere die I2C-Pins für den ESP32
#define I2C_SCL 22
#define I2C_SDA 21
#define I2C_Baud 100000
#define TPS55288_Addr 0x74

// Erstelle eine Instanz der TPS55288-Klasse
TPS55288 tps(I2C_SDA, I2C_SCL, I2C_Baud);

void setup() {
  // Initialisiere die serielle Kommunikation zur Ausgabe
  Serial.begin(115200);
  
  // Initialisiere die I2C-Kommunikation
  //Wire1.begin(I2C_SDA, I2C_SCL);
  
  // Initialisiere das TPS55288-Modul
  //tps = TPS55288(I2C_SDA, I2C_SCL);
  
  // Setze den Spannungsregelmodus
  tps.SetVoltageControl();
  
  // Initialize the logger
  //Debug::begin(LOG_LEVEL_DEBUG);

  // Enable file logging and set log file retention period to 1 minute
  //Debug::enableFileLogging(false);
  //Debug::setLogFileRetentionPeriod(60000);

  // Example log messages
  //Debug::info("System is starting up...");
  //Debug::debug("This is a debug message");
  //Debug::error("This is an error message");

  // Aktiviere den Ausgang
  tps.OutputEnable();
  delay(2000);
  tps.OutputDisable();
  delay(6000);
}

void loop() {
  // Setze eine Testspannung, z.B. 3.3V
  float testVoltage = 3.3;
  tps.SetVoltage(testVoltage);
  
  // Ausgabe der eingestellten Spannung
  Serial.print("Set Voltage: ");
  Serial.println(testVoltage);
  
  // Eine kurze Verzögerung, um die Ausgabe zu stabilisieren
  delay(1000);
}
